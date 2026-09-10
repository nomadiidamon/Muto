#include "mupch.h"

#include "Utils/PlatformUtils.h"

#include <filesystem>
#include <glib.h>
#include <libportal/portal.h>
#include <cstring>
#include <string>
#include <vector>

namespace Muto {

	namespace {

		struct DialogResult
		{
			GMainLoop* Loop = nullptr;
			GVariant* Filters = nullptr;
			std::string Path;
		};

		gboolean QuitDialogLoop(gpointer userData)
		{
			g_main_loop_quit(static_cast<GMainLoop*>(userData));
			return G_SOURCE_REMOVE;
		}

		std::vector<std::string> ExtractPatterns(const char* filter)
		{
			std::vector<std::string> patterns;
			if (!filter)
				return patterns;

			const char* description = filter;
			while (*description != '\0')
			{
				const char* pattern = description + std::strlen(description) + 1;
				if (*pattern == '\0')
					break;

				std::string patternText(pattern);
				std::size_t patternPosition = 0;
				while (patternPosition < patternText.size())
				{
					const std::size_t separator = patternText.find(';', patternPosition);
					const std::size_t end = separator == std::string::npos ? patternText.size() : separator;
					if (end > patternPosition)
						patterns.push_back(patternText.substr(patternPosition, end - patternPosition));
					patternPosition = separator == std::string::npos ? patternText.size() : separator + 1;
				}

				description = pattern + std::strlen(pattern) + 1;
			}

			return patterns;
		}

		GVariant* CreateFilters(const char* filter)
		{
			GVariantBuilder builder;
			g_variant_builder_init(&builder, G_VARIANT_TYPE("a(sa(us))"));
			g_variant_builder_open(&builder, G_VARIANT_TYPE("(sa(us))"));
			g_variant_builder_add(&builder, "s", "Files");
			g_variant_builder_open(&builder, G_VARIANT_TYPE("a(us)"));
			for (const std::string& pattern : ExtractPatterns(filter))
				g_variant_builder_add(&builder, "(us)", 0u, pattern.c_str());
			g_variant_builder_close(&builder);
			g_variant_builder_close(&builder);
			return g_variant_builder_end(&builder);
		}

		void CompleteDialog(DialogResult* result, GVariant* response, GError* error)
		{
			if (error)
			{
				MU_CORE_ERROR("Linux file dialog failed: {0}", error->message);
				g_error_free(error);
				g_idle_add(QuitDialogLoop, result->Loop);
				return;
			}

			if (!response)
			{
				MU_CORE_ERROR("Linux file dialog returned no response.");
				g_idle_add(QuitDialogLoop, result->Loop);
				return;
			}

			guint responseCode = 0;
			if (g_variant_lookup(response, "response", "u", &responseCode) && responseCode != 0)
			{
				MU_CORE_INFO("Linux file dialog closed without a selection (response code {0}).", responseCode);
				g_idle_add(QuitDialogLoop, result->Loop);
				return;
			}

			if (response)
			{
				GVariant* uris = g_variant_lookup_value(response, "uris", G_VARIANT_TYPE("as"));
				if (uris)
				{
					const gchar* uri = nullptr;
					g_variant_get_child(uris, 0, "&s", &uri);
					if (uri)
					{
						gchar* path = g_filename_from_uri(uri, nullptr, nullptr);
						if (path)
						{
							result->Path = path;
							g_free(path);
						}
					}
					g_variant_unref(uris);
				}
			}

			g_idle_add(QuitDialogLoop, result->Loop);
		}

		void OpenFileCallback(GObject* source, GAsyncResult* asyncResult, gpointer userData)
		{
			DialogResult* result = static_cast<DialogResult*>(userData);
			GError* error = nullptr;
			GVariant* response = xdp_portal_open_file_finish(XDP_PORTAL(source), asyncResult, &error);
			CompleteDialog(result, response, error);
			if (response)
				g_variant_unref(response);
		}

		void SaveFileCallback(GObject* source, GAsyncResult* asyncResult, gpointer userData)
		{
			DialogResult* result = static_cast<DialogResult*>(userData);
			GError* error = nullptr;
			GVariant* response = xdp_portal_save_file_finish(XDP_PORTAL(source), asyncResult, &error);
			CompleteDialog(result, response, error);
			if (response)
				g_variant_unref(response);
		}

		std::string RunDialog(bool save, const char* filter)
		{
			XdpPortal* portal = xdp_portal_new();
			GMainLoop* loop = g_main_loop_new(nullptr, FALSE);
			DialogResult result{ loop, g_variant_ref_sink(CreateFilters(filter)), {} };

			if (save)
				xdp_portal_save_file(portal, nullptr, "Save File", nullptr, nullptr, nullptr, result.Filters, nullptr, nullptr, XDP_SAVE_FILE_FLAG_NONE, nullptr, SaveFileCallback, &result);
			else
				xdp_portal_open_file(portal, nullptr, "Open File", result.Filters, nullptr, nullptr, XDP_OPEN_FILE_FLAG_NONE, nullptr, OpenFileCallback, &result);

			g_main_loop_run(loop);
			g_variant_unref(result.Filters);
			g_main_loop_unref(loop);
			g_object_unref(portal);
			return result.Path;
		}
	}

	std::string FileDialogs::OpenFile(const char* filter)
	{
		return RunDialog(false, filter);
	}

	std::string FileDialogs::SaveFile(const char* filter)
	{
		return RunDialog(true, filter);
	}

}
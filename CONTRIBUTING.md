# Muto Contributing Guidelines

## Introduction

Welcome to the Muto project! I appreciate your interest in contributing to our codebase. This document outlines the guidelines and best practices for contributing to Muto, ensuring a smooth and efficient collaboration process.

### Code of Conduct

We expect all contributors to adhere to our [Code of Conduct](CODE_OF_CONDUCT.md). Please read it carefully and ensure that your interactions with the community are respectful and inclusive.

### Getting Started

To get started with contributing to Muto, follow these steps:
1. **Fork the Repository**: Create a personal copy of the Muto repository by clicking the "Fork" button on the top right corner of the repository page.
2. **Clone the Repository**: Clone your forked repository to your local machine using the following command:
```bash
git clone --recursive https://github.com/nomadiidamon/Muto <desiredLocation>
```
3. **Set Up the Development Environment**: Follow the instructions in the [README](README.md) *Build* section to set up your development environment and install any necessary dependencies.
4. **Create a New Branch**: Before making any changes, create a new branch for your work to keep your contributions organized and separate from the main branch. Your branch name should be descriptive of the feature or fix you are working on.
5. **Make Changes**: Implement your changes in the codebase. Ensure that your code follows the project's coding standards and best practices.
6. **Test Your Changes**: Run the existing tests and add new tests if necessary to ensure that your changes do not introduce any regressions or issues.
7. **Commit Your Changes**: Commit your changes with clear and concise commit messages.
8. **Push Your Changes**: Push your changes to your forked repository on GitHub.
9. **Create a Pull Request**: Open a pull request (PR) from your forked repository to the main Muto repository. Provide a detailed description of your changes, including the problem you are solving and any relevant context.
10. **Address Feedback**: Be responsive to feedback from reviewers and make any necessary changes to your pull request.
	1. **Review Process**: Your pull request will be reviewed by the maintainers of the Muto project. They may request changes or provide suggestions for improvement. Please be open to feedback and willing to make adjustments as needed.
11. **Merge Your Pull Request**: Once your pull request has been approved and all feedback has been addressed, a maintainer will merge your changes into the main branch.

### Naming Conventions

- Snake_Case/snake_case/snake_Case is fine for private member or local variables.
- camelCase is fine for public member or local variables, although Name is prefered to something like myName.
- Functions should always be uppercase, - DoThing() - unless it is a variant - DoThing_Internal() - in which case Snake_Case is fine.
Examples:
	- Class member variables (private): m_name, m_array, etc.
	- Class member variables (public): Name, myName, Length, applicationConfig, etc.
	- Class Functions (private): DoThing(), DoThing_Internal(), etc.
	- Class Functions (public): DoThing(), DoThingAgain(), etc.
	- Class Static variables (private): s_name, s_array, etc.
	- Class Static variables (public): sName, sArray, etc.
	- Boolean values: bHasAccess, b_Access, etc.

### Coding Standards

To maintain a consistent codebase, please adhere to the following coding standards:
- Follow the existing code style and conventions used in the project.
- Write clear and descriptive variable and function names.
- Include comments and documentation where necessary to explain complex logic or functionality.
- Ensure that your code is modular and reusable, avoiding duplication whenever possible.
- Write unit tests for new features and bug fixes to ensure code quality and maintainability.
- Use version control effectively, making small, focused commits with meaningful commit messages.

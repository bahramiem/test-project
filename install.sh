#!/bin/bash

# Configuration - Replace with your GitHub details
REPO_OWNER="bahramiem"
REPO_NAME="test-project"
BINARY_NAME="port_listener"
INSTALL_DIR="/usr/local/bin"

# Check if running as root
if [ "$EUID" -ne 0 ]; then 
  echo "Please run as root (use sudo)"
  exit 1
fi

echo "Checking for dependencies..."
if ! command -v curl &> /dev/null; then
    echo "Error: curl is not installed. Please install it first."
    exit 1
fi

if [ "$REPO_OWNER" == "<OWNER>" ] || [ "$REPO_NAME" == "<REPOSITORY>" ]; then
    echo "Error: REPO_OWNER and REPO_NAME in install.sh must be updated to your GitHub profile."
    exit 1
fi

echo "Fetching latest release information for $REPO_OWNER/$REPO_NAME..."
LATEST_RELEASE_URL=$(curl -s https://api.github.com/repos/$REPO_OWNER/$REPO_NAME/releases/latest | grep "browser_download_url" | cut -d '"' -f 4 | grep "$BINARY_NAME")

if [ -z "$LATEST_RELEASE_URL" ]; then
    echo "Error: Could not find the latest release or binary for $BINARY_NAME."
    echo "Make sure you have created at least one release with the compiled binary."
    exit 1
fi

echo "Downloading $BINARY_NAME from $LATEST_RELEASE_URL..."
curl -L -o "$BINARY_NAME" "$LATEST_RELEASE_URL"

if [ $? -ne 0 ]; then
    echo "Error: Download failed."
    exit 1
fi

echo "Installing $BINARY_NAME to $INSTALL_DIR..."
mv "$BINARY_NAME" "$INSTALL_DIR/"
chmod +x "$INSTALL_DIR/$BINARY_NAME"

echo "------------------------------------------------"
echo "Installation complete!"
echo "You can now run the listener using: $BINARY_NAME"
echo "------------------------------------------------"

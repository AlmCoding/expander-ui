#!/bin/bash

set -e

echo "📦 Setting up STM32 DFU udev rules..."

# Create udev rule
RULE_FILE="/etc/udev/rules.d/49-stm32dfu.rules"
RULE_CONTENT='ATTRS{idVendor}=="0483", ATTRS{idProduct}=="df11", MODE:="0666", GROUP="plugdev"'

if [ "$(id -u)" -ne 0 ]; then
    echo "❗ This script must be run as root (use sudo)"
    exit 1
fi

# Write the rule
echo "$RULE_CONTENT" > "$RULE_FILE"
echo "✅ udev rule written to $RULE_FILE"

# Reload udev
udevadm control --reload-rules
udevadm trigger
echo "🔄 udev rules reloaded"

# Create plugdev group if it doesn't exist
if ! getent group plugdev > /dev/null; then
    echo "👷‍♂️ Creating 'plugdev' group..."
    groupadd plugdev
fi

# Add current user to plugdev
CURRENT_USER=$(logname)
usermod -aG plugdev "$CURRENT_USER"
echo "👤 Added $CURRENT_USER to plugdev group"

echo ""
echo "ℹ️ You may need to reboot or log out/in for group changes to take effect."


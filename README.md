# ArduinoClient

The client implementation of [ProtoSpecs](https://github.com/CroissantBit/ProtoSpecs)

## Building

This project uses [PlatformIO](https://platformio.org/) to help manage libraries and build/upload the project
PlatformIO supports multiple IDEs and CLI.

Refer to [CLI docs](https://docs.platformio.org/en/latest/core/userguide/index.html) for up-to date info.

```bash
# Clone the repository
git clone https://github.com/CroissantBit/ArduinoClient.git
cd ArduinoClient

# Open the dir in your preferred editor or continue with the CLI
# Modify platformio.ini and env.h files to match your setup (display and board)
# See: https://docs.platformio.org/en/stable/core/quickstart.html
vim platformio.ini
vim src/env.h

# Install the required libs (IDE should do that automatically)
pio pkg install

# Build and upload project
pio run --target upload
```

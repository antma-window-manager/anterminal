SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# Include flags for GTK+ 3 and VTE
CFLAGS = -Wall -Werror $(shell pkg-config --cflags vte-2.91) -I/opt/homebrew/include
LDFLAGS = $(shell pkg-config --libs vte-2.91) -L/opt/homebrew/lib -lconfig

BINNAME = anterminal
APPDIR = anterminal.app/Contents/MacOS
PLIST = anterminal.app/Contents/info.plist

# Default build target
all: $(BINNAME)

# If 'macos' is passed as a target, build the macOS app bundle
macos: $(BINNAME)
	# Create the app bundle directory structure
	mkdir -p $(APPDIR)
	mkdir -p anterminal.app/Contents
	mkdir -p anterminal.app/Contents/MacOS
	mkdir -p anterminal.app/Contents/Resources
	
	# Create the info.plist file inline with correct CFBundleName
	@echo '<?xml version="1.0" encoding="UTF-8"?>' > $(PLIST)
	@echo '<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">' >> $(PLIST)
	@echo '<plist version="1.0">' >> $(PLIST)
	@echo '    <dict>' >> $(PLIST)
	@echo '        <key>CFBundleExecutable</key>' >> $(PLIST)
	@echo '        <string>anterminal</string>' >> $(PLIST)
	@echo '        <key>CFBundleIconFile</key>' >> $(PLIST)
	@echo '        <string>icon</string>' >> $(PLIST)
	@echo '        <key>CFBundleIdentifier</key>' >> $(PLIST)
	@echo '        <string>com.anterminal.anterminal</string>' >> $(PLIST)
	@echo '        <key>CFBundleName</key>' >> $(PLIST)
	@echo '        <string>anterminal</string>' >> $(PLIST)  # Ensure this is correct
	@echo '        <key>CFBundleVersion</key>' >> $(PLIST)
	@echo '        <string>1.0</string>' >> $(PLIST)
	@echo '        <key>CFBundlePackageType</key>' >> $(PLIST)
	@echo '        <string>APPL</string>' >> $(PLIST)
	@echo '    </dict>' >> $(PLIST)
	@echo '</plist>' >> $(PLIST)

	# Copy the binary into the app bundle
	cp $(BINNAME) $(APPDIR)/$(BINNAME)
	@echo "Built macOS app bundle"

$(BINNAME): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS) -lconfig
	rm $(OBJS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm $(BINNAME) $(OBJS)
	rm -rf $(APPDIR)

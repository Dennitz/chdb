.PHONY: all clean buildlib wheel pub mac-arm64

buildlib:
	@echo "Building library..."
	@cd chdb && bash build.sh
	@echo "Done."

wheel:
	@echo "Building wheel..."
	tox -e build -- --wheel
	@echo "Done."

pub:
	@echo "Publishing wheel..."
	tox -e publish
	@echo "Done."

clean:
	@echo "Cleaning..."
	tox -e clean
	@echo "Done."

mac-arm64:
	@echo "Make macOS arm64 whl"
	bash packages/build_mac_arm64.sh
	@echo "Done."

build: clean buildlib wheel

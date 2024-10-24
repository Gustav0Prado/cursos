all: clean
	@echo "#!/bin/bash" >> ./separa
	@echo "" >> ./separa
	@echo "python3 $(shell pwd)/src/main.py \$$@" >> ./separa
	@chmod +x ./separa

clean:
	@rm -rf ./separa ./src/__pycache__
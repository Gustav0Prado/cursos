all: clean
	@echo "#!/bin/bash" >> ./separa
	@echo "" >> ./separa
	@echo "python3 $(shell pwd)/src/main.py \$$@" >> ./separa
	@chmod +x ./separa

clean:
	@rm -f ./separa
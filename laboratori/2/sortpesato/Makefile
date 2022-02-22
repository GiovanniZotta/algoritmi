NUM?=""
build: clean
	@g++ genera_numeri.cpp && ./a.out $(NUM) >> input.txt;
	@g++ sortpesato.cpp -o sortpesato

run: build
	@./sortpesato $(NUM)

clean:
	@rm input.txt

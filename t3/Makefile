all:
	gcc -c curl_code.c -lcurl
	gcc -o Sete_Cliques_Serial curl_code.o sete_cliques_serial.c -lcurl
	gcc -o Sete_Cliques_Threads curl_code.o sete_cliques_threads.c -lcurl -lpthread

serial:
	gcc -c curl_code.c -lcurl
	gcc -o Sete_Cliques_Serial curl_code.o sete_cliques_serial.c -lcurl

threads:
	gcc -c curl_code.c -lcurl
	gcc -o Sete_Cliques_Threads curl_code.o sete_cliques_threads.c -lcurl -lpthread

clean:
	rm curl_code.o
	rm Sete_Cliques

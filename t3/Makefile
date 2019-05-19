all:
	gcc -c curl_code.c -lcurl
	gcc -o Sete_Cliques curl_code.o main.c -lcurl
	gcc -o Sete_Cliques_Serial curl_code.o sete_cliques_serial.c -lcurl
	gcc -o Sete_Cliques_Threads curl_code.o sete_cliques_threads.c -lcurl

serial:
	gcc -c curl_code.c -lcurl
	gcc -o Sete_Cliques_Serial curl_code.o sete_cliques_serial.c -lcurl

threads:
	gcc -c curl_code.c -lcurl
	gcc -o Sete_Cliques_Threads curl_code.o sete_cliques_threads.c -lcurl

clean:
	rm curl_code.o
	rm Sete_Cliques

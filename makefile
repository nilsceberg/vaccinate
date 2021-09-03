vaccinate: vaccinate.o
	$(CC) -o vaccinate $<

clean:
	@rm vaccinate *.o

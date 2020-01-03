    #include <stdio.h>
    int main()
    {
	
	 struct book {
		int num_pages;
		float height;
		float width;
		char *writer;
	}Harry_Potter = {
		32, 40.6, 13.2, "J.k.Rolling"	
	};		
	typedef struct book books;
	books Dog;	
	
	scanf("%d %f %f %s", &Dog.num_pages, &Dog.height, &Dog.width, Dog.writer);
	printf("%d\n", Dog.num_pages);
	printf("%s\n", Dog.writer);
		
		
    return 0;
    }

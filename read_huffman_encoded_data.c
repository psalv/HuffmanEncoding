#include "read_huffman_encoded_data.h"

unsigned char *read_huffman_encoded_data(char *compressed_file_name_ptr, int *image_width, 
	int *image_height, int *max_gray_value, int *number_of_nodes, struct node **huffman_node, 
	long int *length_of_encoded_image){

	struct header* file_header = malloc(sizeof(struct header));

	FILE *f = fopen(compressed_file_name_ptr, "rb");
	fread(file_header, sizeof(struct header), 1, f);

	// Getting the information from the header
	*image_width = file_header->image_width;
	*image_height = file_header->image_height;
	*max_gray_value = file_header->max_gray_value;
	*number_of_nodes = file_header->number_of_nodes;
	*length_of_encoded_image = file_header->length_of_encoded_image;

	// Getting all of the huffman nodes
	*huffman_node = malloc(sizeof(struct node) * (*number_of_nodes));
	for(int i = 0; i < *number_of_nodes; i++){
		huffman_node[i] = malloc(sizeof(struct node));
		fread(huffman_node[i], sizeof(struct node), 1, f);
	}

	printf("\n\n");
	for(int i = 0; i < file_header->number_of_nodes; i++){
		printf("%d %d \n", huffman_node[i]->first_value, huffman_node[i]->second_value);
	}

	// Read in encoded text
	unsigned char* encoded_text = malloc(sizeof(unsigned char) * (*length_of_encoded_image));
	fread(encoded_text, sizeof(unsigned char), *length_of_encoded_image, f);

	fclose(f);
	free(file_header);

	return encoded_text;
}
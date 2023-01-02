#include "JPEG_decoder.hh"

Huffman_table::Huffman_table(uint8_t *data) {
    uint16_t pos = 0;

    this->type = *(data + (++pos)) >> 4;
    this->table_id = *(data + pos) & 0xF;

    this->num_codes_len_i = new uint8_t[16];
    for(int i = 0; i < 16; i++)
        this->num_codes_len_i[i] = *(data + (++pos));

    this->symbol_array = new uint8_t*[16];
    for(int i = 0; i < 16; i++){
        uint8_t num_codes = this->num_codes_len_i[i];
        this->symbol_array[i] = new uint8_t[num_codes];

        for(int j = 0; j < num_codes; j++)
            this->symbol_array[i][j] = *(data + (++pos));
    }
	this->length = pos;

	//Create max and min code values
	int16_t code = 0;
	this->min_code_value = new int16_t[16];
	this->max_code_value = new int16_t[16];
	for(int i = 0; i < 16; i++){
		if(this->num_codes_len_i[i] == 0){
			this->min_code_value[i] = -1;
			this->max_code_value[i] = -1;
			code = code << 1;
			continue;
		}

		this->min_code_value[i] = code;
		this->max_code_value[i] = min_code_value[i] + (this->num_codes_len_i[i] - 1);
		code = (this->max_code_value[i] + 1) << 1;
	}
}

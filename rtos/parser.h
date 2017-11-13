#ifndef __PARSER_H__
#define __PARSER_H__


#include "jsmn.h"

int get_scene(mqtt_message_t *message)
{
	int output = 1;
	char* msg = (char*)message->payload;
	char *node = strstr(msg, "desired");
	if (node) {
		char* val =  strstr(node, "desired");
		char scene = val[9]; 
		switch(scene)
		{
			case '2': 
				output = 2; 
				break;
			case '3': 
				output = 3; 
				break;
			case '4': 
				output = 4; 
				break;
			case '5': 
				output = 5; 
				break;
		}
	}
	
	return output; 
}

/*
int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
			strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}

int parse_json(mqtt_message_t *message) 
{
	char* msg = (char*)message->payload;
	jsmntok_t tokens[64];
	jsmn_parser parser;
	parser.pos = 0;
	int r = jsmn_parse(&parser, msg, message->payloadlen, tokens, 64);

	// Loop over all keys of the root object 
	for (int i = 1; i < r; i++) {
		if (jsoneq(msg, &tokens[i], "desired") == 0) {
			// We may use strndup() to fetch string value 
			printf("- desired: %.*s\n", tokens[i+1].end - tokens[i+1].start,
					msg + tokens[i+1].start);
			i++;
		} 
	}
}
*/

#endif 


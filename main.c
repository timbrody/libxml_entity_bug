#include <stdio.h>
#include <libxml/xmlversion.h>
#include <libxml/globals.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include <libxml/HTMLparser.h>
#include <libxml/HTMLtree.h>
#include <libxml/c14n.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/xmlIO.h>
/* #include <libxml/debugXML.h> */
#include <libxml/xmlerror.h>
#include <libxml/xinclude.h>
#include <libxml/valid.h>

/*
 * unit test for #863166
 *
 *
 */

int main(int argc, char *argv[])
{
	xmlParserCtxtPtr ctxt;
	char buffer[1024];
	size_t read_length;
	FILE *fh;
	int ret;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <source file> <base_dir>\n", argv[0]);
		exit(1);
	}

	fh = fopen(argv[1], "r");
	if (fh == NULL) {
		perror(argv[1]);
		exit(1);
	}

	read_length = fread(buffer, sizeof(char), 4, fh);

	ctxt = xmlCreatePushParserCtxt(NULL, NULL, buffer, read_length, NULL);

	xmlCtxtUseOptions(ctxt, XML_PARSE_DTDLOAD);
	ctxt->directory = argv[2];

	while ((read_length = fread(buffer, sizeof(char), 1024, fh))) {
		ret = xmlParseChunk(ctxt, buffer, read_length, 0);
		if (ret != 0) {
			break;
		}
	}
	ret = xmlParseChunk(ctxt, buffer, 0, 1);

	exit(0);
}

// created date : 2011/11/30 23:04:46
// last updated : 2011/12/01 01:39:58
// libxml2 を利用
// Windows でコンパイルするときは -lws2_32 が必要。
// $ g++ -O2 xml_io.cpp -lm -o xml_io -lxml2 -lws2_32

#include <libxml/xmlwriter.h>
#include <libxml/parser.h>

#include <iostream>
using namespace std;

// 解析のサンプル
void parse(const char *file_name);
// 書き出しのサンプル
void write(const char *file_name);

int main(){
  parse("input.xml");
  write("output.xml");
  return 0;
}

void parse(const char *file_name){
  xmlDocPtr  doc = NULL;
  xmlNodePtr ptr = NULL;
  xmlNodePtr ws = NULL;
  xmlNodePtr ws2 = NULL;
  if((doc = xmlParseFile(file_name)  ) == NULL ||
	 (ptr = xmlDocGetRootElement(doc)) == NULL ){
	cerr << "parse() error" << endl;
	goto END_OF_PARSE_FUNCTION;
  }
  
  // ルートノードの出力
  cout << ptr->name <<  endl; // タグ名
  
  // 子ノードの出力
  for(ws = ptr->children; ws!=NULL; ws = ws->next){
	if(ws->type == XML_ELEMENT_NODE){
	  cout << "  "<< (ws->name); // タグ名
	  // message タグであれば内容を出力
	  if( xmlStrcmp( ws->name, BAD_CAST "message")==0 )
		cout << " '" << ws->children->content << "'";
	  cout <<  endl;

	  // 子ノードの出力
	  for(ws2 = ws->children; ws2!=NULL; ws2 = ws2->next){
		if(ws2->type == XML_ELEMENT_NODE){
		  cout << "    "<< (ws2->name);
		  // lang 属性があれば出力
		  if(xmlHasProp( ws2, BAD_CAST "lang") != NULL)
			cout << " lang=" << xmlGetProp(ws2,BAD_CAST "lang") << " ";
		  // name タグであれば内容を出力
		  if( xmlStrcmp( ws2->name, BAD_CAST "name")==0 )
			cout << " '" << ws2->children->content << "'";
		  cout << endl;
		}
	  }
	  
	}
  }
  cout << endl;

 END_OF_PARSE_FUNCTION:
  if(doc != NULL) xmlFreeDoc(doc);
}

void write(const char *file_name){
  xmlTextWriterPtr writer = NULL;
  
  if( (writer = xmlNewTextWriterFilename(file_name,0)) == NULL ||
	  xmlTextWriterStartDocument(writer, NULL, "UTF-8", NULL) < 0 ){
	cerr << "write() error" << endl;
	goto END_OF_WRITE_FUNCTION;
  }
	
  xmlTextWriterSetIndent(writer, 1);

  xmlTextWriterStartElement(writer, BAD_CAST "root");

  {
	xmlTextWriterStartElement(writer, BAD_CAST "message");
	xmlTextWriterWriteAttribute(writer, BAD_CAST "id", BAD_CAST "0001" );
	xmlTextWriterWriteFormatAttribute(writer, BAD_CAST "number", "%d", 102 );
	xmlTextWriterWriteString(writer, BAD_CAST "Hello");
	xmlTextWriterEndElement(writer);

	xmlTextWriterStartElement(writer, BAD_CAST "message");
	xmlTextWriterWriteString(writer, BAD_CAST "Bye");
	xmlTextWriterEndElement(writer);

	xmlTextWriterStartElement(writer, BAD_CAST "fruit");
	{
	  xmlTextWriterStartElement(writer, BAD_CAST "name");
	  xmlTextWriterWriteAttribute(writer, BAD_CAST "lang", BAD_CAST "en" );
	  xmlTextWriterWriteString(writer, BAD_CAST "Apple");
	  xmlTextWriterEndElement(writer);

	  xmlTextWriterStartElement(writer, BAD_CAST "name");
	  xmlTextWriterWriteAttribute(writer, BAD_CAST "lang", BAD_CAST "ja" );
	  xmlTextWriterWriteString(writer, BAD_CAST "りんご");
	  xmlTextWriterEndElement(writer);
	}
	xmlTextWriterEndElement(writer);
  }
  xmlTextWriterEndElement(writer);

 END_OF_WRITE_FUNCTION:
  if(writer != NULL) xmlFreeTextWriter(writer);

}

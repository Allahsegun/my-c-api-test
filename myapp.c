




#define CURL_STATICLIB
//#include<cJSON.h>;
#include<stdio.h>
#include<curl/curl.h>
#include<stdlib.h>
#include<string.h>




char storedtext[10000];
char* newptr = &storedtext;
size_t datasize;
size_t chucksize;

struct DATA{
	char* mydata;
	size_t len;
};


size_t writeData(char*ptr, size_t data, size_t numdata, void *userdata){
	chucksize = data * numdata;
	printf("%zu\n", chucksize);
	for (size_t a = datasize; a < strlen(ptr); a++){
		newptr[a] = ptr[a];
	}
	datasize += chucksize;
	return chucksize;
}

int main(int a, char* argv[]) {

	//https://accelerexportal.app:8084/anp/api/v3/linuxpostest/login
	//char header[1000] = "content-type:application/json x-source-code:test x-client-id:test ";


	struct DATA data;
	data.mydata = (char*)malloc(1);
	data.mydata[0] = '\0';
	data.len = 0;
	CURL* curl;
	curl = curl_easy_init();

	struct curl_slist* header = NULL;
	header = curl_slist_append(header, "content-type:application/json");
	header = curl_slist_append(header, "x-source-code:test");
	header = curl_slist_append(header, "x-client-id:test");

	curl_easy_setopt(curl, CURLOPT_URL, "https://accelerexportal.app:8084/anp/api/v3/linuxpostest/login");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"userReference\":\"test\",\"terminalId\":\"0000\",\"password\":\"test\",\"deviceId\":\"111111\"}");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, newptr);

	int resCode = curl_easy_perform(curl);
	char* prop = ",\"getProp\":\"balance\"}";

	for (int a = 0; a < strlen(prop); a++) {
		newptr[datasize + a -1] = prop[a];
	}

	
	printf("\nresponse code: %s\n", curl_easy_strerror(resCode));
	printf("\nrespose data:\n %s", newptr );
	printf("\n Total data received :%zu bytes \n", datasize);

	char* json = newptr;
	//printf("my json value:\n%s", json);
	char key[500] = " ";
	char* mykey = &key;
	char value [500] =" ";
	char* myvalue = &value;
	boolean iskey = TRUE;
	char* getprop = "balance";  
	size_t responseLen = strlen(json);
	size_t indexPos = 0;
	//printf("\nrespose length is:%zu\n", responseLen);

	for (size_t a = 0; a < responseLen; a++) { 
		//checking if the key is 
		if (iskey && json[a] != '\"' && json[a] != ':' && json[a] != ',' && json[a] != '{' && json[a] != "" && json[a] != '}') {
			mykey[indexPos] = json[a];
			printf("%c", mykey[indexPos]);
			indexPos++;
		}if (iskey && (json[a] == ':' || json[a] == ',')) {
			printf("\n\ncurrent value of mykey = %s\n", mykey);
			printf("\nkey len = %zu\n", strlen(mykey));
			printf("strcmp = %d", strcmp(mykey,getprop));
			if (strcmp(mykey,getprop) == 0) {
				iskey = FALSE;
				printf("\niskey is false\n");
			}
			// mykey[b] = 0;  repalced by memset
			for (int b = 0; b < strlen(mykey); b++) { memset(mykey, 0, strlen(mykey)); }
			//mykey = "";
			printf("\nthe empty value of mykey = %s\n", mykey);
			indexPos = 0;
		}
		
		// reading the value of.
		if (!iskey && json[a] != '\"' && json[a] != ':' && json[a] != ','  && json[a] != '}') {
			myvalue[indexPos] = json[a];
			indexPos++;
		}if (!iskey && json[a] == ',') {
			a = responseLen;
			printf("\nfinally checked for the value.\n");
		}
	}
	printf("\nbalance : %s\n\n\n", myvalue);
	curl_easy_cleanup(curl);
	curl_slist_free_all(header);
	

	/**/
	//char* postme = "{\"name\" : \"hammed segun\", \"email\" : \"hammed@yahoo.com\", \"id\" : 400, \"getProp\" : \"name\"}";
	
	//printf("balance : ");
	//CURL* getdata;
	//getdata = curl_easy_init();
	//struct curl_slist* newheader = NULL;
	//newheader = curl_slist_append(newheader, "Content-Type:application/json");
	//newheader = curl_slist_append(newheader, "Accept:*/*");
	//curl_easy_setopt(getdata, CURLOPT_HTTPHEADER, newheader);
	//curl_easy_setopt(getdata, CURLOPT_URL, "http://localhost:4000/api/members/getdata");
	//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"name\" : \"hammed\", \"email\" : \"hammed@yahoo.com\", \"id\" : 200, \"getProp\" : \"name\"}");
	//curl_easy_setopt(curl, CURLOPT_POSTFIELDS,newptr);
	//int res = curl_easy_perform(getdata);
	//printf("\nrequest code: %s", curl_easy_strerror(res));
	//curl_easy_cleanup(getdata);

	//curl_slist_free_all(newheader);
	
	//printf("\n execution finished");
	 

	return 0;
}

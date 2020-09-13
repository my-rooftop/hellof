#include <torch/script.h> //One-stop header.
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <typeinfo>
#include <vector>
#include <iostream>
#include <memory>
#include <typeinfo>
#include <string>
#include <bitset>
#include <map>
#include <stdlib.h>
#include <sys/time.h>
extern "C" {
	#include "xmatchPro.h"
}

using namespace std;


// int xmatchCompress(unsigned char* input, int size, unsigned char* output) {
// 	int retValue;
// 	unsigned int* orgSize = (unsigned int*) output;

// 	struct xmatchContext* compContext = (struct xmatchContext*) malloc(sizeof(struct xmatchContext));


// 	//The first 4bytes is the original size of data.(number of integers)
// 	createXmatchContext(compContext, input, size, (output + 4));
// 	(*orgSize) = (unsigned int) compContext->inputSize;
	
// 	retValue = xmatchEncode(compContext) + 4;

// 	destroyXmatchContext(compContext);

// 	return retValue;
// };


int hash_256[256] = {0};


int file_int[4096] = {};
bitset<8> file_bit[4096] = {};
unsigned char file_char[4096] = {};


class information_Node* ptr1 = 0;
class information_Node* information_table[200000] = {ptr1};



class information_Node
{	
public:
	bitset<13> compressed_length;
	bitset<32> saved_location;
	bitset<20> reference;
	bitset<1> deduped;
	bitset<1> self_compressed;
};



class Node* hash_table[50000] = {};//32768

class Node
{
public:
	bitset<256> hash_in_node;
	class Node* next;
	int refer;
	bitset<8> file_in_node[4096];
};

map<size_t, int> dedup;



int main(int argc, const char* argv[]) {
	if (argc != 2) {
		std::cerr << "usage: example-app <path-to-exported-script-module>\n";
		return -1;
	}
	//cout << "here" << endl;
	FILE* input = fopen("web", "rb");
	if (input == NULL) {
		printf("cannot open\n");
		return 0;
	}

	FILE* f = fopen("output", "wb");

	torch::jit::script::Module module;
	try {
		module = torch::jit::load(argv[1]);
	}
	catch (const c10::Error& e) {
		std::cerr << "error loading the model\n";
		return -1;
	}
	auto opts = torch::TensorOptions().dtype(torch::kInt32);
	unsigned long long sum1 = 0;
	unsigned long long sum2 = 0;
	unsigned long long sum4 = 0;
	unsigned long long sum5 = 0;
	unsigned long long sum6 = 0;
	unsigned long long sum7 = 0;
	unsigned long long sum8 = 0;
	unsigned long long sum9 = 0;
	unsigned long long sum10 = 0;
	unsigned long long sum11 = 0;
	unsigned long long sum12 = 0;
	unsigned long long sum13 = 0;
	unsigned long long sum14 = 0;
	unsigned long long sum15 = 0;
	unsigned long long sum16 = 0;
	int u1 = 0;
	int u2 = 0;
	int u4 = 0;
	int u5 = 0;
	int u6 = 0;
	int u7 = 0;
	int u8 = 0;
	int u9 = 0;
	int u10 = 0;
	int u11 = 0;
	int u12 = 0;
	int u13 = 0;
	int u14 = 0;
	int u15 = 0;
	int u16 = 0;
	int com_mean = 0;
	int com_count = 0;
	struct timeval startTime, endTime;
	struct timeval startTime1, endTime1;
	unsigned long long diffTime;

	for (int u = 0; u < 100000; u++) {
		if(u % 10000 == 0){
			cout << u << endl;
		}

		gettimeofday(&startTime, NULL);
		int num[1] = {};
		for(int i = 0; i < 4096; i++){
			fread(num, 1, 1, input);
			file_int[i] = num[0];
			file_bit[i] = bitset<8>(num[0]);
			file_char[i] = (unsigned char)num[0];
		}
		gettimeofday(&endTime, NULL);
		diffTime = (endTime.tv_sec - startTime.tv_sec)*1000000 + endTime.tv_usec - startTime.tv_usec;
		if(diffTime < 100000000000){
			u6 = u6 + 1;
			sum6 = sum6 + (unsigned long long)diffTime;
		}//242

		gettimeofday(&startTime, NULL);
		string str;
		for(int i = 0; i < 4096; i++){
			str += (char)file_int[i];
		}
		gettimeofday(&endTime, NULL);
		diffTime = (endTime.tv_sec - startTime.tv_sec)*1000000 + endTime.tv_usec - startTime.tv_usec;
		if(diffTime < 100000000000){
			u5 = u5 + 1;
			// cout << "Passing Network : " << diffTime << endl;
			sum5 = sum5 + (unsigned long long)diffTime;
		}

		gettimeofday(&startTime, NULL);
		size_t d = std::hash<string>{}(str);
		gettimeofday(&endTime, NULL);
		diffTime = (endTime.tv_sec - startTime.tv_sec)*1000000 + endTime.tv_usec - startTime.tv_usec;
		if(diffTime < 100000000000){
			u7 = u7 + 1;
			// cout << "Passing Network : " << diffTime << endl;
			sum7 = sum7 + (unsigned long long)diffTime;
		}


		if (dedup.count(d) == 1){
			//add information to information_table		
			//save data
			gettimeofday(&startTime, NULL);
			class information_Node* inode = new information_Node;
			inode->deduped = bitset<1>(1);
			inode->compressed_length = bitset<13>(0);
			inode->saved_location = bitset<32>(0);
			inode->reference = bitset<20>(dedup[d]);
			inode->self_compressed = bitset<1>(0);

			information_table[u] = inode;
			delete inode;
			gettimeofday(&endTime, NULL);

			diffTime = (endTime.tv_sec - startTime.tv_sec)*1000000 + endTime.tv_usec - startTime.tv_usec;
			if(diffTime < 100000000000){
				u4 = u4 + 1;
				// cout << "Passing Network : " << diffTime << endl;
				sum4 = sum4 + (unsigned long long)diffTime;

			}

		}
		else {
			dedup[d] = u;

			gettimeofday(&startTime, NULL);
            torch::Tensor t = torch::from_blob(file_int, {1, 4096}, opts);
			gettimeofday(&endTime, NULL);
			diffTime = (endTime.tv_sec - startTime.tv_sec)*1000000 + endTime.tv_usec - startTime.tv_usec;
			if(diffTime < 100000000000){
				u8 = u8 + 1;
				// cout << "Passing Network : " << diffTime << endl;
				sum8 = sum8 + (unsigned long long)diffTime;

			}

			gettimeofday(&startTime, NULL);
			t = (t - 128) / 128.0;
			gettimeofday(&endTime, NULL);
			if(diffTime < 100000000000){
				u9 = u9 + 1;
				// cout << "Passing Network : " << diffTime << endl;
				sum9 = sum9 + (unsigned long long)diffTime;

			}

			std::vector<torch::jit::IValue> inputs;
			inputs.push_back(t);
			//line by line
			gettimeofday(&startTime, NULL);
			auto t1 = module.forward(inputs).toTensor();
			gettimeofday(&endTime, NULL);

			diffTime = (endTime.tv_sec - startTime.tv_sec)*1000000 + endTime.tv_usec - startTime.tv_usec;
			if(diffTime < 100000000000){
				u1 = u1 + 1;
				// cout << "Passing Network : " << diffTime << endl;
				sum1 = sum1 + (unsigned long long)diffTime;

			}
			// for (int j = 0; j < 256; j++) {
			// 	cout << t1[0][j].item<float>() << endl;
			// }

			gettimeofday(&startTime, NULL);
			for (int j = 0; j < 256; j++) {
				if (t1[0][j].item<float>() <= 0) {
					hash_256[j] = 0;
				}
				else {
					hash_256[j] = 1;
				}
			}
			gettimeofday(&endTime, NULL);

			diffTime =  (endTime.tv_sec - startTime.tv_sec)*1000000 + endTime.tv_usec - startTime.tv_usec;
			if(diffTime < 100000000000){
				u2 = u2 + 1;
				// cout << "1 or 0 : " << diffTime << endl;
				sum2 = sum2 + (unsigned long long)diffTime;
			}

			gettimeofday(&startTime, NULL);
			string hash_string;
			for (int j = 0; j < 256; j++) {
				hash_string += to_string(hash_256[j]);
			}
			gettimeofday(&endTime, NULL);
			diffTime =  (endTime.tv_sec - startTime.tv_sec)*1000000 + endTime.tv_usec - startTime.tv_usec;
			if(diffTime < 100000000000){
				u10 = u10 + 1;
				// cout << "1 or 0 : " << diffTime << endl;
				sum10 = sum10 + (unsigned long long)diffTime;
			}
			// gettimeofday(&startTime, NULL);
			unsigned long index;
			string split;
			// gettimeofday(&endTime, NULL);
			// diffTime = endTime.tv_usec - startTime.tv_usec;
			// cout << "PLISE LOOK" << diffTime << endl;
			gettimeofday(&startTime, NULL);
			split = hash_string.substr(236, 15);
			index = int(bitset<15>(split).to_ulong());
			gettimeofday(&endTime, NULL);
			diffTime =  (endTime.tv_sec - startTime.tv_sec)*1000000 + endTime.tv_usec - startTime.tv_usec;
			if(diffTime < 100000000000){
				u11 = u11 + 1;
				// cout << "1 or 0 : " << diffTime << endl;
				sum11 = sum11 + (unsigned long long)diffTime;
			}
			//cout << index << endl;

			bitset<256> hash_value;
			hash_value = bitset<256>(hash_string);
			if (hash_table[index] == NULL){
				// gettimeofday(&startTime, NULL);
				// gettimeofday(&endTime, NULL);
				// diffTime = (endTime.tv_sec - startTime.tv_sec)*1000000 + endTime.tv_usec - startTime.tv_usec;
				// if(diffTime < 100000000000){
				// 	u6 = u6 + 1;
				// 	sum6 = sum6 + (unsigned long long)diffTime;
				// }
				gettimeofday(&startTime, NULL);
				class Node* node = new Node;
				hash_table[index] = node;
				node->hash_in_node = hash_value;
				node->next = NULL;
				for(int t = 0; t < 4096; t++){
					node->file_in_node[t] = file_bit[t];
				}
				gettimeofday(&endTime, NULL);
				diffTime =  (endTime.tv_sec - startTime.tv_sec)*1000000 + endTime.tv_usec - startTime.tv_usec;
				if(diffTime < 100000000000){
					u12 = u12 + 1;
					sum12 = sum12 + (unsigned long long)diffTime;
				}
				//add information


				node->refer = ftell(f);
				//file save
				unsigned char* output = (unsigned char*)malloc(9999);
				// for (int y = 15; y < 20; y++){
				// 	cout << file_bit[y] << endl;
				// }
				gettimeofday(&startTime, NULL);
				int compressedSize = xmatchCompress(file_char, 4096, output);
				gettimeofday(&endTime, NULL);
				diffTime =  (endTime.tv_sec - startTime.tv_sec)*1000000 + endTime.tv_usec - startTime.tv_usec;
				if(diffTime < 100000000000){
					u13 = u13 + 1;
					sum13 = sum13 + (unsigned long long)diffTime;
				}
				//cout << ftell(f) << endl;
				com_mean = com_mean + compressedSize;
				com_count = com_count + 1;
				fwrite(output, compressedSize, 1, f);

				//cout << ftell(f) << endl;
				free(output);

				gettimeofday(&startTime, NULL);
				class information_Node* inode = new information_Node;
				inode->deduped = bitset<1>(0);
				inode->compressed_length = bitset<13>(compressedSize);
				inode->saved_location = bitset<32>(node->refer);
				inode->reference = bitset<20>(0);
				inode->self_compressed = bitset<1>(1);
				// cout << "inode->deduped : "<< (inode->deduped).to_ulong() << endl;
				// cout << "inode->compressed_length : "<< (inode->compressed_length).to_ulong() << endl;
				// cout << "inode->saved_location : "<< (inode->saved_location).to_ulong() << endl;
				// cout << "inode->reference : "<< (inode->reference).to_ulong() << endl;
				// cout << "inode->self_compressed : "<< (inode->self_compressed).to_ulong() << endl;
				information_table[u] = inode;
				gettimeofday(&endTime, NULL);
				diffTime =  (endTime.tv_sec - startTime.tv_sec)*1000000 + endTime.tv_usec - startTime.tv_usec;
				if(diffTime < 100000000000){
					u14 = u14 + 1;
					sum14 = sum14 + (unsigned long long)diffTime;
				}
				delete inode;
				//filesave

			}
            else if(hash_table[index] != NULL){
				class Node* start_point;
				start_point = hash_table[index];
				int trigger = 0;
				gettimeofday(&startTime1, NULL);
				while (trigger == 0){
					if (start_point->hash_in_node == hash_value){
						//cout << "pass1" << endl;
						trigger = 1;
						//add information
						//file save
						//XOR
						// for (int y = 15; y < 20; y++){
						// 	cout << file_bit[y] << endl;
						// }
						gettimeofday(&startTime, NULL);
						for(int j = 0; j < 4096; j++){
							file_bit[j] = start_point->file_in_node[j] ^= file_bit[j]; 
						}
						gettimeofday(&endTime, NULL);
						diffTime =  (endTime.tv_sec - startTime.tv_sec)*1000000 + endTime.tv_usec - startTime.tv_usec;
						if(diffTime < 100000000000){
							u16 = u16 + 1;
							sum16 = sum16 + (unsigned long long)diffTime;
						}
						// for (int y = 15; y < 20; y++){
						// 	cout << file_bit[y] << endl;
						// }
						
						unsigned char* output = (unsigned char*)malloc(9999);
						unsigned char* input = (unsigned char*)malloc(4096);
						for(int q = 0; q < 4096; q++){
							input[q] =static_cast<unsigned char>(file_bit[q].to_ulong());
						}
						int loca = ftell(f);
						int compressedSize = xmatchCompress(input, 4096, output);
						com_mean = com_mean + compressedSize;
						com_count = com_count + 1;
						//cout << ftell(f) << endl;
						fwrite(output, 1, compressedSize, f);
						//cout << ftell(f) << endl;

						
						class information_Node* inode = new information_Node;
						inode->deduped = bitset<1>(0);
						inode->compressed_length = bitset<13>(compressedSize);
						inode->saved_location = bitset<32>(loca);
						inode->reference = bitset<20>(start_point->refer);
						inode->self_compressed = bitset<1>(0);
						information_table[u] = inode;
						delete inode;
						free(input);
						free(output);

					}
					else if(start_point->hash_in_node != hash_value){
						if(start_point->next == NULL){
							//cout << "pass2" << endl;
							class Node* node = new Node;
							node->hash_in_node = hash_value;
							node->next = NULL;
							for (int y = 0; y<4096; y++){
								node->file_in_node[y] = file_bit[y];
							}
							start_point->next = node;
							trigger = 1;
							
							node->refer = ftell(f);
							//file save
							unsigned char* output = (unsigned char*)malloc(9999);
							int compressedSize = xmatchCompress(file_char, 4096, output);
							com_mean = com_mean + compressedSize;
							com_count = com_count + 1;
							//cout << ftell(f) << endl;
							fwrite(output, 1, compressedSize, f);
							//cout << ftell(f) << endl;
							free(output);

							class information_Node* inode = new information_Node;
							inode->deduped = bitset<1>(0);
							inode->compressed_length = bitset<13>(compressedSize);
							inode->saved_location = bitset<32>(node->refer);
							inode->reference = bitset<20>(0);
							inode->self_compressed = bitset<1>(1);

							// cout << "inode->deduped : "<< inode->deduped << endl;
							// cout << "inode->compressed_length : "<< inode->compressed_length << endl;
							// cout << "inode->saved_location : "<< inode->saved_location << endl;
							// cout << "inode->reference : "<< inode->reference << endl;
							// cout << "inode->self_compressed : "<< inode->self_compressed << endl;

							information_table[u] = inode;
							delete inode;
							//add information
							

						}
						else if( start_point->next != NULL){
							start_point = start_point->next;
						}
					}
				}
			gettimeofday(&endTime1, NULL);
			diffTime =  (endTime1.tv_sec - startTime1.tv_sec)*1000000 + endTime1.tv_usec - startTime1.tv_usec;
			if(diffTime < 100000000000){
				u15 = u15 + 1;
				sum15 = sum15 + (unsigned long long)diffTime;
			}
			}

			// if(diffTime > 1000){
			// 	cout << "here" << u << endl;
			// }
			// cout << "Passing Network : " << sum1 << endl;
			// cout << "adding hash _ and save : " << sum3 << endl;

			// FILE* f = fopen("output", "wb");
			// char toStore[4096];

			// if (hash_table[index] == ptr){
			// 	fwrite(toStore, 1, 3000, f);
			// }

			// char buf[10000];
			// fseek(f, 5000, SEEK_SET);
			// fread(buf, 1, 1234, f);
			
			// fseek(f, 0, SEEK_END);

			// char input[9999], output[9999];
			// int compressedSize = XmathCompress(input, 4096, output);
			// // fwrite(toStore, 1, compressedSize, f);
			// cout << hash_string << endl;
			// cout << "information" << "[" << u << "]" << endl;
			// cout << "compressed_length is : " << (information_table[u]->compressed_length).to_ulong() << endl;
			// cout << "deduped? : "<<information_table[u]->deduped << endl;
			// cout << "reference : " << (information_table[u]->reference).to_ulong() << endl;
			// cout << "saved_location : " << (information_table[u]->saved_location).to_ulong() << endl;
			// cout << "self_compressed : " << information_table[u]->self_compressed << endl;
		}
		
	}
	FILE* foo = fopen("information", "wb");
	cout << sizeof(*information_table[0]) << endl;
	for (int j = 0; j < 100000; j++){
		fwrite(information_table[j], sizeof(*information_table[j]), 1, foo);
	}

	// class information_Node
	// {	
	// public:
	// 	bitset<13> compressed_length;
	// 	bitset<32> saved_location;
	// 	bitset<20> reference;cd
	// 	bitset<1> deduped;
	// 	bitset<1> self_compressed;
	// };
	fclose(input);
	fclose(f);
	fclose(foo);
	cout << "Passing Network <u1> : " << sum1 / u1 << endl;
	cout << "1 or 0 <u2> : " << sum2 / u2 << endl;
	cout << "<u4> : " << sum4 / u4 << endl;
	cout << "<u5> : " << sum5 / u5 << endl;
	cout << "<u6> : " << sum6 / u6 << endl;
	cout << "<u7> : " << sum7 / u7 << endl;
	cout << "<u8> : " << sum8 / u8 << endl;
	cout << "<u9> : " << sum9 / u9 << endl;
	cout << "<u10> : " << sum10 / u10 << endl;
	cout << "<u11> : " << sum11 / u11 << endl;
	cout << "<u12> : " << sum12 / u12 << endl;
	cout << "<u13> : " << sum13 / u13 << endl;
	cout << "<u14> : " << sum14 / u14 << endl;
	cout << "<u15> : " << sum15 / u15 << endl;
	cout << "<u16> : " << sum16 / u16 << endl;
	cout << "compressed_mean : " << com_mean / com_count << endl;
// struct Info {
// 	int;
// };

// Info information[N];


// 	FILE* info = fopen();
// 	for (int i = 0; i < N; ++i) {
// 		printf("%d %d %d %d %d\n", information[i].length, ~.position);
// 	}
// 	fwrite(&information[0], sizeof(Info), N, info);

// 	fread(&information[0], sizeof(Info), N, info);
	return 0;
}
        //auto t1 = m
     
//	std::vector<torch::jit::IValue> inputs;
	
	
	/*

      
	torch::jit::script::Module module;
	try {
		module = torch::jit::load(argv[1]);
	}
	catch (const c10::Error& e) {
		std::cerr << "error loading the model\n";
		return -1;
	}


	//at::Tensor output = module.forward(inputs).toTensor();
	//std::cout << output << '\n';
	//std::cout << "parameters : " << '\n';

//	for (const auto& p : module.parameters()) {
//		std::cout << p << std::endl;
//	
	vector<int> data_vector;
	auto opts = torch::TensorOptions().dtype(torch::kInt32);
	for (int i = 0; i < 234054; i++) {
		data_vector = DATA[i];
		torch::Tensor t = torch::from_blob(data_vector.data(), {1, 4096}, opts).to(torch::kInt64);
		t = (t - 128) / 128.0;
		std::vector<torch::jit::IValue> inputs;
		inputs.push_back(t);
		 
		auto t1 = module.forward(inputs).toTensor();
                
		
		for (int j = 0; j < 256; j++) {
			if (t1[0][j].item<int>() <= 0) {
				output[i][j] = 0;
			}
			else {
				output[i][j] = 1;
			}
		}
	}
	


	ofstream writeFile;
	writeFile.open("test.txt");
	if(writeFile.is_open()) {
		for (int i = 0; i < 234054; i++) {
			for (int j = 0; j < 256; j++) {
				writeFile << output[i][j];
			}
		}
		writeFile.close();
	}
	

	
	
	//cout << output << '\n';
	
	
	//	auto t2 = torch::nn::functional::cross_entropy(output, target);
		//if (i % 8710 == 0) {
		//	cout << "@@@@@@i is@@@@ : " << i <<t << '\n';
		//}
	//}
	//*/




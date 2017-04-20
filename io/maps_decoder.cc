//
// Created by admin on 2017/4/21.
//

#include "io/maps_decoder.h"
#include "io/ply_decoder.h"
#include <fstream>
#include<vector>
#include <cstdlib>
#include <cstring>
#include <sstream>

bool MapsDecoder::DecodeFromFile(const std::string &file_name, Mesh *out_mesh){
    DecoderBuffer* buffer;
    readFile(file_name);
    ProducePlyBuffer(buffer);
    PlyDecoder ply_decoder;
    return ply_decoder.DecodeFromBuffer(buffer,out_mesh);
}

void MapsDecoder::readFile(const std::string &file_name){
    std::ifstream file(file_name, std::ios::binary);
    if (!file)
        return false;
    //read the number
    char number_line[255];
    file.getline(number_line, 255);
    vector<string> numbers = split(string(number_line), '\t');
    bv_num = atoi(numbers[0].c_str());
    sv_num = atoi(numbers[1].c_str()) - bv_num;
    bf_num = atoi(numbers[2].c_str());

    //read datas
    char num_buffer[255];
    char face_buffer[255];
    for(int i=0; i<bv_num; i++){
        file.getline(num_buffer, 255);
        strcat(bv, num_buffer+3);
    }
    for(int i=0; i<sv_num; i++){
        file.getline(num_buffer, 255);
        strcat(sv, num_buffer+3);
    }
    for(int i=0; i<bf_num; i++){
        file.getline(num_buffer, 255);
        strcpy(face_buffer, "3 ");
        strcat(face_buffer, num_buffer+3);
        strcat(bf, face_buffer);
    }
    file.close();
}

bool MapsDecoder::ProducePlyBuffer(DecoderBuffer* buffer){
    char temp_num[0];
    char temp_buffer[] = ""
            "ply\n"
            "format ascii 1.0\n"
            "element vertex ";
    int2str(bv, temp_num);
    strcat(temp_num, "\n");
    strcat(temp_buffer, temp_num);

    strcat(temp_buffer, ""
            "property   float32   x\n"
            "property   float32   y\n"
            "property   float32   z\n"
            "element face ");
    int2str(bf, temp_num);
    strcat(temp_num, "\n");
    strcat(temp_buffer, temp_num);

    strcat(temp_buffer, ""
            "property list uchar int vertex_indices\n"
            "end_header\n");

    buffer_.Init(&temp_buffer[0], strlen(temp_buffer));
    buffer = &buffer_;
}

vector<string> split(string& str,const char* c)
{
    char *cstr, *p;
    vector<string> res;
    cstr = new char[str.size()+1];
    strcpy(cstr,str.c_str());
    p = strtok(cstr,c);
    while(p!=NULL)
    {
        res.push_back(p);
        p = strtok(NULL,c);
    }
    return res;
}

void int2str(const int &int_temp, char* num)
{
    string string_temp;
    stringstream stream;
    stream<<int_temp;
    stream>>string_temp;
    strcpy(num, string_temp.c_str());
}
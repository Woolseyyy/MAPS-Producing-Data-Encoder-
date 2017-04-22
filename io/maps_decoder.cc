//
// Created by admin on 2017/4/21.
//

#include "io/maps_decoder.h"
#include "io/ply_decoder.h"
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>


void int2str(const int &int_temp, char* num);
std::vector<std::string> split(std::basic_string<char, std::char_traits<char>, std::allocator<char>> str, const char* c);

void MapsDecoder::BufferFromFile(const std::string &file_name){
    readFile(file_name);
    ProducePlyBuffer();
}

bool MapsDecoder::Decode(draco::Mesh *out_mesh){
    draco::PlyDecoder ply_decoder;
    return ply_decoder.DecodeFromBuffer(&mesh_buffer_,out_mesh) ;
}

bool MapsDecoder::Decode(draco::PointCloud *out_point_cloud){
    draco::PlyDecoder ply_decoder;
    return ply_decoder.DecodeFromBuffer(&vector_buffer_,out_point_cloud) ;
}

void MapsDecoder::readFile(const std::string &file_name){
    std::ifstream file(file_name, std::ios::binary);
    //read the number
    char number_line[255];
    file.getline(number_line, 255);
    std::vector<std::string> numbers = split(std::string(number_line), "\t");
    strcpy(bv_num_str, numbers[0].c_str());
    strcpy(sv_num_str, numbers[1].c_str());
    strcpy(bf_num_str, numbers[2].c_str());

    bv_num = atoi(numbers[0].c_str());
    sv_num = atoi(numbers[1].c_str());
    bf_num = atoi(numbers[2].c_str());

    bv = (char*)malloc(sizeof(char[255])*bv_num);
    sv = (char*)malloc(sizeof(char[255])*sv_num);
    bf = (char*)malloc(sizeof(char[255])*bf_num);

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

void MapsDecoder::ProducePlyBuffer() {
    ProduceMeshPlyBuffer();
    ProduceVectorPlyBuffer();
}

void MapsDecoder::ProduceMeshPlyBuffer(){
    char* temp_buffer = (char*)malloc(sizeof(char[255])*(bv_num+bf_num+10));

    strcpy(temp_buffer, ""
            "ply\n"
            "format ascii 1.0\n"
            "element vertex ");
    strcat(temp_buffer, bv_num_str);
    strcat(temp_buffer, "\n");
    strcat(temp_buffer, ""
            "property   float32   x\n"
            "property   float32   y\n"
            "property   float32   z\n"
            "element face ");
    strcat(temp_buffer, bf_num_str);
    strcat(temp_buffer, "\n");
    strcat(temp_buffer, ""
            "property list uchar int vertex_indices\n"
            "end_header\n");

    strcat(temp_buffer, bv);
    strcat(temp_buffer, bf);

    mesh_buffer_.Init(&temp_buffer[0], strlen(temp_buffer));
}

void MapsDecoder::ProduceVectorPlyBuffer(){
    char* temp_buffer = (char*)malloc(sizeof(char[255])*(sv_num+10));

    strcpy(temp_buffer, ""
            "ply\n"
            "format ascii 1.0\n"
            "element vertex ");
    strcat(temp_buffer, sv_num_str);
    strcat(temp_buffer, "\n");
    strcat(temp_buffer, ""
            "property   float32   x\n"
            "property   float32   y\n"
            "property   float32   z\n"
            "element face 0\n"
            "property list uchar int vertex_indices\n"
            "end_header\n");

    strcat(temp_buffer, sv);

    vector_buffer_.Init(&temp_buffer[0], strlen(temp_buffer));
}

std::vector<std::string> split(std::basic_string<char, std::char_traits<char>, std::allocator<char>> str, const char* c)
{
    char *cstr, *p;
    std::vector<std::string> res;
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
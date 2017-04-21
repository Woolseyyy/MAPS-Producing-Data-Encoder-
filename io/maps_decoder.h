//
// Created by admin on 2017/4/21.
//

#ifndef DRACO_IO_MESH_MAPS_DECODER_H_
#define DRACO_IO_MESH_MAPS_DECODER_H_

#include <string>

#include "core/decoder_buffer.h"
#include "io/ply_reader.h"
#include "mesh/mesh.h"

class MapsDecoder {
public:
    bool DecodeFromFile(const std::string &file_name, draco::Mesh *out_mesh);
    bool ProducePlyBuffer();

private:
    char bv_num_str[255];
    int bv_num;
    char* bv;
    char sv_num_str[255];
    int sv_num;
    char* sv;
    char bf_num_str[255];
    int bf_num;
    char* bf;
    draco::DecoderBuffer buffer_;

    void readFile(const std::string &file_name);
};


#endif //DRACO_MAPSDECODER_H

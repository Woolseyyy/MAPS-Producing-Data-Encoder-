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
    void BufferFromFile(const std::string &file_name);
    bool Decode(draco::Mesh *out_mesh);
    bool Decode(draco::PointCloud *out_point_cloud);

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
    draco::DecoderBuffer mesh_buffer_;
    draco::DecoderBuffer vector_buffer_;

    void ProducePlyBuffer();
    void ProduceMeshPlyBuffer();
    void ProduceVectorPlyBuffer();
    void readFile(const std::string &file_name);
};


#endif //DRACO_MAPSDECODER_H

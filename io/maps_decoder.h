//
// Created by admin on 2017/4/21.
//

#ifndef DRACO_MAPSDECODER_H
#define DRACO_MAPSDECODER_H

#include <string>

#include "core/decoder_buffer.h"
#include "io/ply_reader.h"
#include "mesh/mesh.h"

class MapsDecoder {
public:
    bool DecodeFromFile(const std::string &file_name, Mesh *out_mesh);
    bool ProducePlyBuffer(DecoderBuffer* buffer);

private:
    int bv_num;
    char bv[0];
    int sv_num;
    char sv[0];
    int bf_num;
    char bf[0];
    DecoderBuffer buffer_;

    void readFile(const std::string &file_name);
};


#endif //DRACO_MAPSDECODER_H

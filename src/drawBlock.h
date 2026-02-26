#pragma once

#include "ofMain.h"
#include "blockGenerator.h"

class drawBlock {
    public:
        drawBlock(float _cellSize = 40.0f, float _blockHeight = 40.0f);

        void setCellSize(float _cellSize);
        void setBlockHeight(float _blockHeight);
        void setOrigin(const glm::vec3& _origin);

        void drawGrid(const blockData& data) const;
        void drawBlocks(const blockData& data) const;
        void draw(const blockData& data) const;

    private:
        float cellSize;
        float blockHeight;
        glm::vec3 origin;
};

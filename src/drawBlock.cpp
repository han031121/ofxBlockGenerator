#include "drawBlock.h"

drawBlock::drawBlock(float _cellSize, float _blockHeight)
    : cellSize(_cellSize), blockHeight(_blockHeight), origin(0.0f, 0.0f, 0.0f) {}

void drawBlock::setCellSize(float _cellSize) {
    cellSize = _cellSize;
}

void drawBlock::setBlockHeight(float _blockHeight) {
    blockHeight = _blockHeight;
}

void drawBlock::setOrigin(const glm::vec3& _origin) {
    origin = _origin;
}

void drawBlock::drawGrid(const blockData& data) const {
    const int rows = data.getMaxRow();
    const int cols = data.getMaxCol();

    ofPushStyle();
    ofSetColor(110);

    for (int r = 0; r <= rows; ++r) {
        const float z = origin.z + r * cellSize;
        ofDrawLine(origin.x, origin.y, z,
                   origin.x + cols * cellSize, origin.y, z);
    }

    for (int c = 0; c <= cols; ++c) {
        const float x = origin.x + c * cellSize;
        ofDrawLine(x, origin.y, origin.z,
                   x, origin.y, origin.z + rows * cellSize);
    }

    ofPopStyle();
}

void drawBlock::drawBlocks(const blockData& data) const {
    const int rows = data.getMaxRow();
    const int cols = data.getMaxCol();
    const int maxHeight = data.getMaxHeight();

    ofPushStyle();
    ofSetColor(80, 180, 255);

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            for (int h = 1; h <= maxHeight; ++h) {
                if (!data.getData(r, c, h)) {
                    continue;
                }

                const float centerX = origin.x + c * cellSize + cellSize * 0.5f;
                const float centerY = origin.y - (h - 0.5f) * blockHeight;
                const float centerZ = origin.z + r * cellSize + cellSize * 0.5f;

                ofDrawBox(centerX, centerY, centerZ,
                          cellSize * 0.92f, blockHeight * 0.92f, cellSize * 0.92f);
            }
        }
    }

    ofPopStyle();
}

void drawBlock::draw(const blockData& data) const {
    drawGrid(data);
    drawBlocks(data);
}

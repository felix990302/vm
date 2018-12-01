#include "model/ptr_cursor.h"
#include "brace_match.h"
#include "match_brace_motion.h"


namespace VM {
    Cursor MatchBraceMotion::nextPosition(const PtrCursor &cursor) {
        char currChar = *cursor;

        Cursor position {cursor.getLine(), cursor.getCol()+1};
        auto it = OpenBraceMatch.find(currChar);
        if(it != OpenBraceMatch.end()) {
            size_t openBraceCount = 0;
            char matchChar = it->second;
            for(auto lineIt=cursor.getLineIterator(); lineIt!=cursor.getLineEnd(); ++lineIt, ++position.line) {
                const std::string &currLine = *lineIt;
                for(;position.col<currLine.size(); ++position.col) {
                    if(currLine[position.col] == currChar) ++openBraceCount;
                    else if(currLine[position.col] == matchChar && openBraceCount--==0) return position;
                }
                position.col = 0;
            }  
        }

        position = Cursor {cursor};
        it = CloseBraceMatch.find(currChar);
        if(it != CloseBraceMatch.end()) {
            size_t closeBraceCount = 0;
            char matchChar = it->second;
            for(auto lineIt=cursor.getReverseLineIterator(); lineIt!=cursor.getLineReverseEnd(); ++lineIt, --position.line) {
                const std::string &currLine = *lineIt;
                while(position.col--) {
                    if(currLine[position.col] == currChar) ++closeBraceCount;
                    else if(currLine[position.col] == matchChar && closeBraceCount--==0) return position;
                }
                if(lineIt != cursor.getLineReverseEnd() - 1) position.col = (lineIt+1)->size();
            }  
        }
        
        return cursor;
    }
}

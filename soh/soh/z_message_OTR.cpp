#include "OTRGlobals.h"
#include "ResourceMgr.h"
#include "Scene.h"
#include "message_data_static.h"
#include "Utils/StringHelper.h"
#include "global.h"
#include "vt.h"
#include <Text.h>
#include <unordered_map>

extern "C" MessageTableEntry* sNesMessageEntryTablePtr;
extern "C" MessageTableEntry* sGerMessageEntryTablePtr;
extern "C" MessageTableEntry* sFraMessageEntryTablePtr;
extern "C" MessageTableEntry* sStaffMessageEntryTablePtr;
// extern "C" MessageTableEntry* _message_0xFFFC_nes;

static std::unordered_map<u16, std::string> sAccessibilityText;
static std::string sTextInterpolated;
extern "C" void OTRMessage_InitAccessibilityText() {
    auto file = std::static_pointer_cast<Ship::Text>(OTRGlobals::Instance->context->GetResourceManager()->LoadResource(
        "text/accessibility_text/accessibility_text_eng"));

    if (file == nullptr)
        return;

    for (int i = 0; i < file->messages.size(); i++) {
        sAccessibilityText[file->messages[i].id] = file->messages[i].msg;
    }
}
extern "C" const char* OTRMessage_GetAccessibilityText(const char* textResourcePath, u16 textId, const char* arg) {
    auto it = sAccessibilityText.find(textId);
    if (it == sAccessibilityText.end()) {
        return nullptr;
    }

    if (arg != nullptr) {
        sTextInterpolated = it->second;
        std::string searchString = "$0";
        size_t index = sTextInterpolated.find(searchString);
        if (index != std::string::npos) {
            sTextInterpolated.replace(index, searchString.size(), std::string(arg));
            return sTextInterpolated.c_str();
        }
    }

    return it->second.c_str();
}


MessageTableEntry* OTRMessage_LoadTable(const char* filePath, bool isNES) {
    auto file = std::static_pointer_cast<Ship::Text>(OTRGlobals::Instance->context->GetResourceManager()->LoadResource(filePath));

    if (file == nullptr)
        return nullptr;
    
    MessageTableEntry* table = (MessageTableEntry*)malloc(sizeof(MessageTableEntry) * file->messages.size());

    for (int i = 0; i < file->messages.size(); i++) {
        table[i].textId = file->messages[i].id;
        table[i].typePos = (file->messages[i].textboxType << 4) | file->messages[i].textboxYPos;
        table[i].segment = file->messages[i].msg.c_str();
        table[i].msgSize = file->messages[i].msg.size();

        if (isNES && file->messages[i].id == 0xFFFC)
            _message_0xFFFC_nes = (char*)file->messages[i].msg.c_str();
    }

    return table;
}

extern "C" void OTRMessage_Init()
{
    sNesMessageEntryTablePtr = OTRMessage_LoadTable("text/nes_message_data_static/nes_message_data_static", true);
    sGerMessageEntryTablePtr = OTRMessage_LoadTable("text/ger_message_data_static/ger_message_data_static", false);
    sFraMessageEntryTablePtr = OTRMessage_LoadTable("text/fra_message_data_static/fra_message_data_static", false);

    auto file2 = std::static_pointer_cast<Ship::Text>(OTRGlobals::Instance->context->GetResourceManager()->LoadResource("text/staff_message_data_static/staff_message_data_static"));

    sStaffMessageEntryTablePtr = (MessageTableEntry*)malloc(sizeof(MessageTableEntry) * file2->messages.size());

    for (int i = 0; i < file2->messages.size(); i++)
    {
        sStaffMessageEntryTablePtr[i].textId = file2->messages[i].id;
        sStaffMessageEntryTablePtr[i].typePos = (file2->messages[i].textboxType << 4) | file2->messages[i].textboxYPos;
        sStaffMessageEntryTablePtr[i].segment = file2->messages[i].msg.c_str();
        sStaffMessageEntryTablePtr[i].msgSize = file2->messages[i].msg.size();
    }

    OTRMessage_InitAccessibilityText();
}
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is CBash code.
 *
 * The Initial Developer of the Original Code is
 * Waruddar.
 * Portions created by the Initial Developer are Copyright (C) 2010
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
#include "..\..\..\Common.h"
#include "..\BOOKRecord.h"

namespace Ob
{
UINT32 BOOKRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
    {
    switch(FieldID)
        {
        case 0: //recType
            return GetType();
        case 1: //flags1
            return UINT32_FLAG_FIELD;
        case 2: //fid
            return FORMID_FIELD;
        case 3: //flags2
            return UINT32_FLAG_FIELD;
        case 4: //eid
            return ISTRING_FIELD;
        case 5: //full
            return STRING_FIELD;
        case 6: //modPath
            return ISTRING_FIELD;
        case 7: //modb
            return FLOAT32_FIELD;
        case 8: //modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODL.IsLoaded() ? MODL->MODT.GetSize() : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 9: //iconPath
            return ISTRING_FIELD;
        case 10: //text
            return STRING_FIELD;
        case 11: //script
            return FORMID_FIELD;
        case 12: //enchantment
            return FORMID_FIELD;
        case 13: //enchantPoints
            return UINT16_FIELD;
        case 14: //flags
            return UINT8_FLAG_FIELD;
        case 15: //teaches
            return SINT8_FIELD;
        case 16: //value
            return UINT32_FIELD;
        case 17: //weight
            return FLOAT32_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * BOOKRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    switch(FieldID)
        {
        case 1: //flags1
            return &flags;
        case 2: //fid
            return &formID;
        case 3: //flags2
            return &flagsUnk;
        case 4: //eid
            return EDID.value;
        case 5: //full
            return FULL.value;
        case 6: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 7: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 8: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 9: //iconPath
            return ICON.value;
        case 10: //text
            return DESC.value;
        case 11: //script
            return SCRI.IsLoaded() ? &SCRI.value : NULL;
        case 12: //enchantment
            return ENAM.IsLoaded() ? &ENAM.value : NULL;
        case 13: //enchantPoints
            return ANAM.IsLoaded() ? &ANAM.value : NULL;
        case 14: //flags
            return &DATA.value.flags;
        case 15: //teaches
            return &DATA.value.teaches;
        case 16: //value
            return &DATA.value.value;
        case 17: //weight
            return &DATA.value.weight;
        default:
            return NULL;
        }
    return NULL;
    }

bool BOOKRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(UINT32 *)FieldValue);
            break;
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(UINT32 *)FieldValue);
            break;
        case 4: //eid
            EDID.Copy((STRING)FieldValue);
            break;
        case 5: //full
            FULL.Copy((STRING)FieldValue);
            break;
        case 6: //modPath
            MODL.Load();
            MODL->MODL.Copy((STRING)FieldValue);
            break;
        case 7: //modb
            MODL.Load();
            MODL->MODB.value = *(FLOAT32 *)FieldValue;
            break;
        case 8: //modt_p
            MODL.Load();
            MODL->MODT.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 9: //iconPath
            ICON.Copy((STRING)FieldValue);
            break;
        case 10: //text
            DESC.Copy((STRING)FieldValue);
            break;
        case 11: //script
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 12: //enchantment
            ENAM.value = *(FORMID *)FieldValue;
            return true;
        case 13: //enchantPoints
            ANAM.value = *(UINT16 *)FieldValue;
            break;
        case 14: //flags
            SetFlagMask(*(UINT8 *)FieldValue);
            break;
        case 15: //teaches
            DATA.value.teaches = *(SINT8 *)FieldValue;
            break;
        case 16: //value
            DATA.value.value = *(UINT32 *)FieldValue;
            break;
        case 17: //weight
            DATA.value.weight = *(FLOAT32 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void BOOKRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    BOOKDATA defaultDATA;

    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //flags2
            flagsUnk = 0;
            return;
        case 4: //eid
            EDID.Unload();
            return;
        case 5: //full
            FULL.Unload();
            return;
        case 6: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 7: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 8: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 9: //iconPath
            ICON.Unload();
            return;
        case 10: //text
            DESC.Unload();
            return;
        case 11: //script
            SCRI.Unload();
            return;
        case 12: //enchantment
            ENAM.Unload();
            return;
        case 13: //enchantPoints
            ANAM.Unload();
            return;
        case 14: //flags
            DATA.value.flags = defaultDATA.flags;
            return;
        case 15: //teaches
            DATA.value.teaches = defaultDATA.teaches;
            return;
        case 16: //value
            DATA.value.value = defaultDATA.value;
            return;
        case 17: //weight
            DATA.value.weight = defaultDATA.weight;
            return;
        default:
            return;
        }
    return;
    }
}
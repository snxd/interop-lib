## String

String helper functions.

### String_ConvertToHex

Convert binary data to a hex string.

|Name|Type|Description|
|-|-|-|
|Binary|const uint8_t*|Binary data.|
|BinarySize|int32_t|Size of binary data.|
|Lower|bool|Lowercase hex characters if _true_, otherwise uppercase if _false_.|
|Hex|char*|Hex buffer.|
|MaxHex|int32_t|Max hex buffer.|

Return true if successfully, false otherwise.

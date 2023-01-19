## Base64 <!-- omit in toc -->

Base64 functions useful for sending binary data back to JavaScript.

- [Base64\_Encode](#base64_encode)
- [Base64\_CalculateEncodeSize](#base64_calculateencodesize)

### Base64_Encode

Encode binary data to base64.

bool Base64_CalculateEncodeSize(int32_t SourceLength, int32_t *BytesRequired);

|Name|Type|Description|
|-|-|-|
|Source|const uint8_t*|Binary source data.|
|SourceLength|int32_t|Size of binary source data.|
|Target|char*|Base64 target buffer.|
|MaxTarget|int32_t|Max size of base64 target buffer.|
|TargetLength|int32_t*|Pointer to length of bytes copied to target buffer.|

Return true if successfully, false otherwise. When successful, _TargetLength_ will contain the length of the base64 string.

### Base64_CalculateEncodeSize

Calculate the length of the buffer needed for base64 conversion.

|Name|Type|Description|
|-|-|-|
|SourceLength|int32_t|Length of binary source data.|
|BytesRequired|int32_t*|Bytes required to convert source data to base64.|

Returns true if successful, false otherwise. When successful, _BytesRequired_ will contain the number of bytes required for base64 string.
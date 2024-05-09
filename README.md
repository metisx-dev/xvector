# XVECTOR

Vector Similarity Search Acceleration Library

## Setup
### Clone source code
```
git clone https://github.com/metisx-dev/xvector.git
```

### Docker setup

```
./docker-build.sh
```
Docker image가 Dockerfile에 준비되어 있으니, build 스크립트만 실행하시면 자동으로 docker 환경에 접근할 수 있습니다.

## Catch2 FPGA Example
### Build

```
mkdir build && cd build
cmake ..
make
```

위 shell 실행 시 build/example 폴더에 example-catch2라는 실행 파일이 생성됩니다.

### Run example
이 실행파일은 example/example_catch2.cpp 파일을 빌드하며, 샘플 케이스 몇 가지가 포함되어 있습니다.

```
./example-catch2
```
하단 출력은 랜덤생성한 Query vector를, resource/100000-3072-h.npy file에서 로드한 10만개의 vector embedding에 대해 Top-10 knn search를 4번 동일하게 요청한 것으로, query batch가 정상적으로 같은 결과를 출력함을 보여주는 예제입니다.

```
Extended k-NN Search Example with 4 Queries and Target Vector Array
Metadata: 0x55a7829f9690
[0] EMBEDDING, 23429, 0.010326, 0xAB005B85(2868903936)
[1] EMBEDDING, 31900, 0.007633, 0xAB007C9C(2868903936)
[2] EMBEDDING, 25160, 0.006693, 0xAB006248(2868903936)
[3] EMBEDDING, 29790, 0.006441, 0xAB00745E(2868903936)
[4] EMBEDDING, 24411, 0.005694, 0xAB005F5B(2868903936)
[5] EMBEDDING, 11209, 0.005464, 0xAB002BC9(2868903936)
[6] EMBEDDING, 9610, 0.005392, 0xAB00258A(2868903936)
[7] EMBEDDING, 6658, 0.004859, 0xAB001A02(2868903936)
[8] EMBEDDING, 11874, 0.004560, 0xAB002E62(2868903936)
[9] EMBEDDING, 10077, 0.004400, 0xAB00275D(2868903936)

Metadata: 0x55a7829f9690
[0] EMBEDDING, 23429, 0.010326, 0xAB005B85(2868903936)
[1] EMBEDDING, 31900, 0.007633, 0xAB007C9C(2868903936)
[2] EMBEDDING, 25160, 0.006693, 0xAB006248(2868903936)
[3] EMBEDDING, 29790, 0.006441, 0xAB00745E(2868903936)
[4] EMBEDDING, 24411, 0.005694, 0xAB005F5B(2868903936)
[5] EMBEDDING, 11209, 0.005464, 0xAB002BC9(2868903936)
[6] EMBEDDING, 9610, 0.005392, 0xAB00258A(2868903936)
[7] EMBEDDING, 6658, 0.004859, 0xAB001A02(2868903936)
[8] EMBEDDING, 11874, 0.004560, 0xAB002E62(2868903936)
[9] EMBEDDING, 10077, 0.004400, 0xAB00275D(2868903936)

Metadata: 0x55a7829f9690
[0] EMBEDDING, 23429, 0.010326, 0xAB005B85(2868903936)
[1] EMBEDDING, 31900, 0.007633, 0xAB007C9C(2868903936)
[2] EMBEDDING, 25160, 0.006693, 0xAB006248(2868903936)
[3] EMBEDDING, 29790, 0.006441, 0xAB00745E(2868903936)
[4] EMBEDDING, 24411, 0.005694, 0xAB005F5B(2868903936)
[5] EMBEDDING, 11209, 0.005464, 0xAB002BC9(2868903936)
[6] EMBEDDING, 9610, 0.005392, 0xAB00258A(2868903936)
[7] EMBEDDING, 6658, 0.004859, 0xAB001A02(2868903936)
[8] EMBEDDING, 11874, 0.004560, 0xAB002E62(2868903936)
[9] EMBEDDING, 10077, 0.004400, 0xAB00275D(2868903936)

Metadata: 0x55a7829f9690
[0] EMBEDDING, 23429, 0.010326, 0xAB005B85(2868903936)
[1] EMBEDDING, 31900, 0.007633, 0xAB007C9C(2868903936)
[2] EMBEDDING, 25160, 0.006693, 0xAB006248(2868903936)
[3] EMBEDDING, 29790, 0.006441, 0xAB00745E(2868903936)
[4] EMBEDDING, 24411, 0.005694, 0xAB005F5B(2868903936)
[5] EMBEDDING, 11209, 0.005464, 0xAB002BC9(2868903936)
[6] EMBEDDING, 9610, 0.005392, 0xAB00258A(2868903936)
[7] EMBEDDING, 6658, 0.004859, 0xAB001A02(2868903936)
[8] EMBEDDING, 11874, 0.004560, 0xAB002E62(2868903936)
[9] EMBEDDING, 10077, 0.004400, 0xAB00275D(2868903936)
```


해당 케이스는 한 번에 4개의 Query batch를 모아 계산하는 예제만을 실행한 결과로, 20240508 현재 FPGA 구성으로는 19개의 Query를 동시에 계산할 수 있습니다.

이 외에 지원되는 예제는 Query batch 1개에 대한 간단한 knn 예제와, vector들의 distance 계산 예제가 있습니다.
추가적인 예시와 기능 지원은 추후 계속 업데이트될 예정입니다.

## Java

빌드 후 CMake 바이너리 디렉토리의 `java` 하위디렉토리에 `xvector.jar`, `libxvector-jni-sim.so`, `libxvector-jni.so`가 생성됩니다.

실행 시 `.so` 파일들이 위치한 디렉토리를 `-Djava.library.path`로, `xvector.jar`의 경로를 `-cp` 옵션으로 지정해주어야 합니다.

```
java -Djava.library.path=build/Debug/java -cp build/Debug/java/xvector.jar:build/Debug/java/example/gson-2.10.1.jar:build/Debug/java/example/XVectorExample.jar XVectorExample
```

## Status

대부분의 함수는 `xvecStatus`를 반환합니다. 성공 시 `XVEC_SUCCESS`를, 실패 시 에러 정보를 나타내는 `XVEC_ERROR_XXXX`를 반환합니다.

```c
xvecContext context;
xvecStats status = xvecCreateContext(&context, NULL);
if(status != XVEC_SUCCESS)
{
    // Error Handling Here
}
```

모든 함수 호출에 대해 반환 값을 검사하는 것이 안전합니다. 이 문서의 예제 코드에서는 간결함을 위해 검사를 생략합니다.

## Context

Context는 Vector 가속 연산을 수행하기 위해 필요한 자원/상태를 초기화 및 관리하는 인스턴스입니다. Context가 파괴되면 Context와 연관된 모든 객체도 파괴됩니다. 객체들은 `xvecBuffer`, `xvecVectorArray`, `xvecIndexArray`, `xvecFilter`, `xvecKnnQuery`, `xvecKnnResult`, `xvecDistanceQuery`, `xvecDistanceResult`가 있습니다.

```c
#include <xvector.h>
...
    
xvecContext context;
xvecCreateContext(&context, NULL); // Create a context

// Perform Vector Operations
...

xvecDestroyContext(context); // Destroy the context
```

## Reference Counting

`Context`를 제외한 모든 객체는 참조 카운팅으로 구현됩니다. 특별히 함수의 설명에 예외적인 언급이 없다면 다음과 같은 규칙이 적용됩니다.

- `xvecCreate~()`로 생성된 객체의 최초 참조 카운트는 `1`입니다.
- `xvecRelease~()`는 참조 카운트를 `1` 감소시키며, 참조 카운트가 `0`이 되면 객체를 파괴합니다.

- 객체를 인자로 받는 `xvecSet~()`함수는 객체를 참조 카운트를 증가시킵니다. 그러므로 Caller는 즉시 `xvecRelease~()`를 호출할 수 있습니다.

- 객체를 반환하는 `xvecGet~()` 함수들은 참조 카운트를 증가시킨 후 반환합니다. 그러므로 Caller는 해당 객체를 참조할 필요가 없어질 때 반드시 `xvecRelease~()`를 호출해야 합니다.

## Buffer

Buffer는 Device의 메모리에 할당된 공간을 나타냅니다. Buffer를 생성하고, Host의 메모리로부터 Buffer로 데이터를 복사하거나, Buffer로부터 Host의 메모리로 데이터를 복사할 수 있습니다.

```c
...
xvecBuffer buffer;
xvecCreateBuffer(&buffer, context, sizeInBytes); // Create a buffer
...
xvecCopyHostToBuffer(buffer, data, offsetInBytes, sizeInBytes); // Copy data from host to device
...
xvecCopyBufferToHost(data, buffer offsetInBytes, sizeInBytes); // Copy data from device to host
...
xvecReleaseBuffer(); // Release the buffer
```

CXL 장치와 같이 Host에서 Device 메모리에 직접 접근이 가능한 경우, Buffer로부터 포인터를 얻어와 바로 Read/Write를 수행할 수 있습니다.

```c
float* pointer;
status = xvecGetBufferAddress(buffer, (void*)&pointer); // Get Address of the buffer
pointer[0] = 1.0f;
float f = pointer[0];
```

## VectorArray

VectorArray는 이름 그대로 Vector들에 대한 배열입니다. Device의 메모리에 계산할 Vector들을 저장하기 위해 사용되는 객체입니다.

```c
const size_t dimension = 3;
const size_t vectorCount = 10;

// 10 vectors
float vectors[dimension * vectorCount] = {
   0.01f, 0.02f, 0.03f, // 0,
   0.04f, 0.05f, 0.06f, // 1,
   0.07f, 0.08f, 0.09f, // 2,
   0.10f, 0.11f, 0.12f, // 3,
   0.13f, 0.14f, 0.15f, // 4,
   0.16f, 0.17f, 0.18f, // 5,
   0.19f, 0.20f, 0.21f, // 6,
   0.22f, 0.23f, 0.24f, // 7,
   0.25f, 0.26f, 0.27f, // 8,
   0.28f, 0.29f, 0.30f, // 9,
};

xvecBuffer vectorBuf;

xvecCreateBuffer(&vectorBuf, context, sizeof(vectors)); // Create a buffer to hold vectors. The reference count of the buffer is 1.

xvecCopyHostToBuffer(vectorBuf, vectors, 0, sizeof(vectors)); // Copy vectors to the buffer

xvecVectorArray vectorArray;
status = xvecCreateVectorArray(&vectorArray, context, dimension); // Create a vector array.

xvecSetVectorArrayBuffer(vectorArray, vectorBuf, NULL, vectorCount); // Set the buffer to vector array. Now, the reference count of the buffer is 2.

xvecReleaseBuffer(vectorBuf); // The reference count of the buffer is 1, so the buffer is still alive.

...
    
xvecReleaseVectorArray(vectorArray) // Here, when the vector array is destroyed, the buffer is also destroyed.
```

## IndexArray

IndexArray는 VectorArray에 속한 Vector들에 대한 Index들을 가지는 배열입니다. Index를 통해 Vector들을 간접적으로 참조하게 되며, VectorArray의 일부 Vector들에 대해서만 계산하고 싶을 때 IndexArray를 사용할 수 있습니다.

예를 들어 Inverted File Index(IVF) 구현 시 각각의 Cluster를 IndexArray로 표현할 수 있습니다.

```c
xvecIndex indices[] = { 0, 2, 4, 6, 8 };

xvecBuffer indexBuf;
xvecCreateBuffer(&indexBuf, context, sizeof(indices)); // Create a buffer to hold indices.

xvecCopyHostToBuffer(indexBuf, indices, 0, sizeof(indices)); // Copy indices to the buffer

xvecIndexArray indexArray;
xvecCreateIndexArray(&indexArray, vectorArray); // Create an index array

xvecSetIndexArrayIndices(indexArray, indexBuf, sizeof(indices) / sizeof(xvecIndex)); // The reference count of the buffer is increased.

xvecReleaseBuffer(indexBuf); // The reference count of the buffer is decreased.

...

xvecReleaseIndexArray(indexArray) // The index array and the buffer are destroyed.
```

## KnnQuery

Target Array들(VecorArray들 또는 IndexArray들)에 속한 Vector들로부터 Query Vector에 대한 k개의 Exact Nearest Neighbors을 찾습니다. 즉 모든 Vector들에 대해 Score(Distance)를 계산하고 정렬합니다.

각 Query는 여러 Target Array들에 대한 계산을 한 번에 요청 할 수 있습니다. 또한 여러 Query들을 한 번에 실행 요청 할 수 있습니다. 성능을 높이기 위해서는 가능한 많은 VectorArray/IndexArray들과 Query들을 모아서 한 번에 호출하는 것이 좋습니다. 더 정확히는 동일한 Target Vector에 대한 계산이 많이 포함된 쿼리들끼리 모아서 한 번에 실행시켜야 높은 성능을 발휘할 수 있습니다.

서로 다른 종류의 쿼리(KnnQuery, DistanceQuery)들도 동시에 실행시킬 수 있습니다. 동일한 Target Vector를 공유하는 Query들 간에는 최대한 모아서 실행시키는 것이 좋습니다.

```c
const size_t k = 3;
const size_t dimension = 3;

float queryVector[] = { 0.05f, 0.06f, 0.07f };

xvecKnnQuery query;
xvecCreateKnnQuery(&query, context, XVEC_KNN_DOT_PRODUCT, queryVector, dim, k); // Create KnnQuery

// Multiple VectorArrays can be calculated at once.
// To maximize throughput, compute as many VectorArrays as possible at once.
xvecVectorArray vectorArrays[] = { vectorArray0, vectorArray1 };
xvecSetKnnQueryTargets(query, XVEC_KNN_TARGET_VECTOR_ARRAY, vectorArrays, 2); // Set Target Vectors

// IndexArray can also be used:
// xvecIndexArray indexArrays[] = { indexArray0, indexArray1 };
// xvecSetKnnQueryTargets(query, XVEC_KNN_TARGET_INDEX_ARRAY, indexArrays, 2);

// Multiple queries can be perforrmed at once.
// To maximize throughput, perform as many queries as possible at once.
xvecKnnQuery queries[] = { query, queryOther };
xvecExecuteQuery(quries, 2); // Search k Nearest Neighbors

xvecKnnResult result;
xvecGetKnnQueryResult(query, &result); // Get the result.

xvecReleaseKnnQuery(query);  // After getting the result, the query can be released immediately.

float* scores;
xvecGetKnnResultScores(result, &scores); // Get the scores of the top-k vectors sorted by score.

xvecIndex* indices;
xvecGetKnnResultIndices(result, &indices); // Get the indices of the top-k vectors sorted by score.

xvecVectorArray* vectorArrays;
xvecGetKnnResultVectorArrays(result, &vectorArrays); // Get the vector arrays of the top-k vectors sorted by score.

...

xvecReleaseKnnResult(result); // Release the result.
```

현재는 Dot Product 만 지원합니다. 추후 L2 Distance도 지원할 계획입니다. Cosine Similarity를 구현하고 싶다면 VectorArray에 Normalize된 Vector들을 저장하고 Dot Product를 사용하세요. 추후에는 Normalize에 대한 가속 API도 제공할 예정입니다.

## DistanceQuery

VecorArray들 또는 IndexArray들에 속한 Vector들의 Distance 값들을 구합니다.

마찬가지로 가능한 많은 VectorArray/IndexArray들과 Query들을 모아서 한 번에 호출하는 것이 성능에 좋습니다.

```c
const size_t dimension = 3;

float queryVector[] = { 0.05f, 0.06f, 0.07f };

xvecDistanceQuery query;
xvecCreateDistanceQuery(&query, context, XVEC_DISTANCE_DOT_PRODUCT, queryVector, dim); // Create DistanceQuery

// Multiple VectorArrays can be calculated at once.
// To maximize throughput, calculate as many VectorArrays as possible at once.
xvecVectorArray vectorArrays[] = { vectorArray0, vectorArray1 };
xvecSetDistanceQueryTargets(query, XVEC_DISTANCE_TARGET_VECTOR_ARRAY, vectorArrays, 2); // Set Target Vectors

// IndexArray can also be used:
// xvecIndexArray indexArrays[] = { indexArray0, indexArray1 };
// xvecSetDistanceQueryTargets(query, XVEC_DISTANCE_TARGET_INDEX_ARRAY, indexArrays, 2);

// Multiple queries can be perforrmed at once.
// To maximize throughput, perform as many queries as possible at once.
xvecKnnQuery queries[] = { query, queryOther };
xvecExecuteQuery(queries, 2); // Calculate distances

xvecDistanceResult result;
xvecGetDistanceQueryResult(query, &result); // Get the result.

xvecReleaseDistanceQuery(query);  // After getting the result, the query can be released immediately.

float* distances;
xvecGetDistanceResultValues(result, &distance); // Get the distance values

...

xvecReleaseDistanceReault(result); // Release the result
```

현재는 Dot Product 만 지원합니다. 추후 L2 Distance도 지원할 계획입니다. Cosine Similarity를 구하고 싶다면 VectorArray에 Normalize된 Vector들을 저장하고 Dot Product를 사용하세요. 추후에는 Normalization에 대한 가속 API도 제공할 예정입니다.

## Filter

VectorArray의 일부만 계산하고 싶을 경우 IndexArray를 사용해도 되지만 Filter도 사용할 수 있습니다. Filter는 계산에 참여시킬 Vector에 대한 Bitmap입니다. 1로 설정된 Vector들만 계산에 참여합니다.

Pre-filtering과 vector들의 delete/insert를 구현할 때 사용할 수 있습니다. 계산해야 할 Vector의 수가 적다면 Index가, 많다면 Filterr가 효율적일 수 있습니다.

처음 VectorArray에 설정한 Vector 중 일부를 삭제하려고 할 때 특히 유용합니다. Filter가 없다면 매번 Vector Array에 대한 Buffer를 새로 만들어서 설정하거나 상당히 많은 엔트리를 가지는 IndexArray를 만들어야 할 것입니다. Filter를 사용하면 Bitmap을 저장하는 Buffer들을 만들어 유지한 후 이를 업데이트하면 됩니다.

Filter를 Query에 설정된 Target Array 수 보다 적게 설정할 경우 남은 Array들은 Filter가 적용되지 않습니다(즉, 모든 Vector들을 계산). 또한 Filter에 NULL을 주는 경우에도 해당 Array의 모든 Vector들을 계산하게 됩니다.

```c
...

size_t filterSize = (vectorCount + 7) / 8;
size_t validCount = 0;
uint8_t bitmap[filterSize];

memset(bitmap, 0, filterSize);

// Intent to count only even-positioned vectors
for (size_t i = 0; i < vectorCount; i += 2)
{
    bitmap[i / 8] |= 1 << (i % 8);
    ++validCount;
}

xvecBuffer bitmapBuf;
xvecCreateBuffer(&bitmapBuf, context, filterSize); // Create a buffer to store bitmap

xvecCopyHostToBuffer(bitmapBuf, bitmap, 0, filterSize); // Copy bitmap to the device

xvecFilter filter;
xvecCreateFilter(&filter, context); // Create Filter

xvecSetFilterBuffer(filter, bitmapBuf, validCount); // Set bitmap buffer to the filter.

xvecReleaseBuffer(bitmapBuf); // The buffer can be released immediately.

// Suppose there are three target arrays.
//  - The first array does not use a filter.
//  - For the second array, only the even-positioned vectors participate in the calculation.
//  - The third array does not use a filter.
xvecBuffer filters[] = { NULL, filter };

xvecSetKnnQueryFilters(query, filters, 2); // Set the filters to the query.

xvecReleaseFilter(filter); // The filter can be released immediately.

...

```

IndexArray에 대한 Filter를 제공하는 것도 가능합니다.

## Element-wise operations

+, -, * 지원 계획에 있습니다.

## FPGA 사용 시 주의사항
간혹 정상적인 실행파일을 실행하더라도 오랫동안 (10s 이상) terminal에 반응이 없는 경우에는 FPGA가 오류 state에 있는 상태이므로, MetisX의 서버 관리자에게 문의하시기 바랍니다.

FPGA를 관리하는 스크립트나 라이브러리는 추후 업데이트될 예정입니다.
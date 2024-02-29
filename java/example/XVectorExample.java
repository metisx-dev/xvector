import com.metisx.xvector.*;

public class XVectorExample {
    public static void main(String[] args) {
        try {
            String jarPath = XVectorExample.class.getProtectionDomain().getCodeSource().getLocation().toURI().getPath();
            String jarDir = new java.io.File(jarPath).getParent();

            final int dimension = 3072;
            final int vectorCount = 100;

            String npyPath = jarDir + "/resources/100-3072.npy";
            System.out.println("npyPath=" + npyPath);

            Npy npy = new Npy(npyPath);
            float[] sampleData = npy.floatElements();

            // 1. Create Context
            Context context = new Context();

            // 2. Create Vector Array
            VectorArray vectorArray = new VectorArray(context, dimension);

            {
                Buffer vectorBuffer = new Buffer(context, (long)vectorCount * dimension * Float.BYTES);

                vectorBuffer.copyHostToBuffer(sampleData, 0, vectorCount * dimension);

                vectorArray.setBuffer(vectorBuffer, vectorCount);

                vectorBuffer.close();
            }

            // 3. k-NN Search - Vector Array

            {
                final int k = 10;
                System.out.println("-- k-NN Search with VectorArray --");

                KnnQuery query = new KnnQuery(context, OpType.DOT_PRODUCT, QueryVectors.vector, dimension, k);

                query.setTarget(vectorArray);

                Query.execute(query);

                KnnResult result = query.getResults();

                int resultK = result.getK();
                int[] kIndices = result.getIndices();
                float[] kScores = result.getScores();

                System.out.println("resultK=" + resultK);
                for (int i = 0; i < resultK; i++) {
                    System.out
                            .println("[" + i + "] " + String.valueOf(kIndices[i]) + ", " + String.valueOf(kScores[i]));
                }

                query.close();
                result.close();
            }

            // 4. k-NN Search - Vector Array with Filter

            {
                final int k = 10;
                final int filterSize = (vectorCount + 7) / 8;

                System.out.println("-- k-NN Search with VectorArray and Filter --");

                Filter filter = new Filter(context);
                Buffer filterBuffer = new Buffer(context, (long)(vectorCount + 7) / 8);
                byte[] bitmap = new byte[filterSize];

                for (int i = 0; i < filterSize; ++i) {
                    bitmap[i] = 0;
                }

                int validCount = 0;
                for (int i = 0; i < vectorCount; i += 2) {
                    bitmap[i / 8] |= 1 << (i % 8);
                    ++validCount;
                }

                filterBuffer.copyHostToBuffer(bitmap, 0, filterSize);

                filter.setBuffer(filterBuffer, validCount);

                KnnQuery query = new KnnQuery(context, OpType.DOT_PRODUCT, QueryVectors.vector, dimension, k);

                query.setTarget(vectorArray);
                query.setFilter(filter);

                Query.execute(query);

                KnnResult result = query.getResults();

                int resultK = result.getK();
                int[] kIndices = result.getIndices();
                float[] kScores = result.getScores();

                System.out.println("resultK=" + resultK);
                for (int i = 0; i < resultK; i++) {
                    System.out
                            .println("[" + i + "] " + String.valueOf(kIndices[i]) + ", " + String.valueOf(kScores[i]));
                }

                query.close();
                result.close();
            }

            // 5. Create Index Arrays

            IndexArray[] indexArrays = { null, null, null, null };

            for (int i = 0; i < 4; i++) {
                indexArrays[i] = new IndexArray(vectorArray);

                Buffer indexBuffer = new Buffer(context, (long)25 * Integer.BYTES);

                int[] indices = new int[25];
                for (int j = 0; j < 25; ++j) {
                    indices[j] = j * 4 + i;
                }

                indexBuffer.copyHostToBuffer(indices, 0, indices.length);

                indexArrays[i].setBuffer(indexBuffer, indices.length);

                indexBuffer.close();
            }

            // 6. Create Filters

            Filter[] filters = { null, null };
            final int filterCount = filters.length;
            final int filterSize = (vectorCount + 7) / 8;

            for (int i = 0; i < filterCount; i++) {

                filters[i] = new Filter(context);

                Buffer filterBuffer = new Buffer(context, (long)(vectorCount + 7) / 8);
                byte[] bitmap = new byte[filterSize];

                int validCount = 0;
                if (i == 0) {
                    for (int j = 0; j < 13; ++j) {
                        bitmap[j / 8] |= 1 << (j % 8);
                        ++validCount;
                    }
                } else {
                    for (int j = 13; j < 25; ++j) {
                        bitmap[j / 8] |= 1 << (j % 8);
                        ++validCount;
                    }
                }

                filterBuffer.copyHostToBuffer(bitmap, 0, filterSize);
                filters[i].setBuffer(filterBuffer, validCount);

                filterBuffer.close();
            }

            // 7. k-NN Search - Index Array with/without Filter

            for (int f = 0; f < 2; ++f) {
                boolean useFilter = (f % 2) == 1;

                if (useFilter) {
                    System.out.println("-- k-NN Search with IndexArray and Filter --");
                } else {
                    System.out.println("-- k-NN Search with IndexArray --");
                }

                final int k = 10;
                KnnQuery[] queries = { null, null };
                final int queryCount = queries.length;

                for (int q = 0; q < queryCount; q++) {

                    queries[q] = new KnnQuery(context, OpType.DOT_PRODUCT, QueryVectors.vector, dimension, k);

                    if ((q % 2) == 0) {
                        IndexArray[] targets = { indexArrays[1], indexArrays[2] };
                        queries[q].setTargets(targets);
                        if (useFilter) {
                            Filter[] targetFilters = { filters[0], filters[1] };
                            queries[q].setFilters(targetFilters);
                        }
                    } else {
                        IndexArray[] targets = { indexArrays[2], indexArrays[3] };
                        queries[q].setTargets(targets);
                        if (useFilter) {
                            Filter[] targetFilters = { filters[0], filters[1] };
                            queries[q].setFilters(targetFilters);
                        }
                    }
                }

                Query.execute(queries);

                for (int q = 0; q < queryCount; q++) {
                    KnnResult result = queries[q].getResults();

                    int resultK = result.getK();
                    int[] kIndices = result.getIndices();
                    float[] kScores = result.getScores();

                    System.out.println("resultK=" + resultK);
                    for (int i = 0; i < resultK; i++) {
                        System.out.println(
                                "[" + i + "] " + String.valueOf(kIndices[i]) + ", " + String.valueOf(kScores[i]));
                    }

                    result.close();
                    queries[q].close();
                }
            }

            vectorArray.close();
            context.close();

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
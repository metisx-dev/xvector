package com.metisx.xvector;

public class Query {

    static {
        System.loadLibrary("xvector-jni-sim");
    }

    protected Query(Context context) {
        this.context = context;
    }

    public static void execute(Query query) {
        Query[] queries = { query };
        execute(queries);
    }

    public static void execute(Query[] queries) {
        long[] nativeQueries = new long[queries.length];
        for (int i = 0; i < queries.length; i++) {
            nativeQueries[i] = queries[i].nativeObject;
        }
        nativeExecute(nativeQueries);
    }

    private native static void nativeExecute(long[] queries);

    public long nativeObject;
    public Context context;
}

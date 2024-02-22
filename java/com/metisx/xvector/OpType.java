package com.metisx.xvector;

public enum OpType {
    DOT_PRODUCT(0);
    // L2_DISTANCE(1),
    // CONSINE_SIMILARITY(2);

    private final int value;

    OpType(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }
}


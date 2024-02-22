//package com.github.dreamolight.jnpy;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

public class NpyHeader {
	String descr;
	boolean isFortranOrder = false;
	DataType dataType;
	Endian endian;
	int[] shape;

	public static int[] getShape(String shapeString) {
		shapeString = shapeString.replace("(", "");
		shapeString = shapeString.replace(" ", "");
		shapeString = shapeString.replace(")", "");

		String[] arr = shapeString.split(",");

		int[] result = new int[arr.length];
		for (int i = 0; i < arr.length; i++)
			result[i] = Integer.parseInt(arr[i]);

		return result;
	}

	public static NpyHeader getNpyHeader(byte[] data) {
		String str = new String(data);
		str = str.replaceAll(", \\}", "\\}");
		str = str.replace(": (", ": '(");
		str = str.replace(")}", ")'}");

		JsonParser jsonParser = new JsonParser();
		JsonElement element = jsonParser.parse(str);

		JsonObject headerInfo = element.getAsJsonObject();

		String descr = headerInfo.get("descr").getAsString();
		boolean isFortranOrder = headerInfo.get("fortran_order").getAsBoolean();
		String shapeString = headerInfo.get("shape").getAsString();

		return new NpyHeader(descr, isFortranOrder, getShape(shapeString));
	}

	public NpyHeader(String descr, boolean isFortranOrder, int[] shape) {
		this.descr = descr;
		this.isFortranOrder = isFortranOrder;
		this.shape = shape;

		String endianString = descr.substring(0, 1);
		String typeString = descr.substring(1);

		for (Endian ed : Endian.values()) {
			if (ed.toString().equals(endianString)) {
				this.endian = ed;
				break;
			}
		}

		for (DataType dt : DataType.values()) {
			if (dt.toString().equals(typeString)) {
				this.dataType = dt;
				break;
			}
		}
	}

}
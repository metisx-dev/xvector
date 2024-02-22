//package com.github.dreamolight.jnpy;

enum Endian {
	host {
		@Override
		public String toString() {
			return "=";
		}
	},
	big {
		@Override
		public String toString() {
			return ">";
		}
	},
	little {
		@Override
		public String toString() {
			return "<";
		}
	},
	na {
		@Override
		public String toString() {
			return "|";
		}
	}
}

enum DataType {
	bool {
		@Override
		public String toString() {
			return "b1";
		}
	},
	uint8 {
		@Override
		public String toString() {
			return "u1";
		}
	},
	uint16 {
		@Override
		public String toString() {
			return "u2";
		}
	},
	uint32 {
		@Override
		public String toString() {
			return "u4";
		}
	},
	uint64 {
		@Override
		public String toString() {
			return "u8";
		}
	},
	int8 {
		@Override
		public String toString() {
			return "i1";
		}
	},
	int16 {
		@Override
		public String toString() {
			return "i2";
		}
	},
	int32 {
		@Override
		public String toString() {
			return "i4";
		}
	},
	int64 {
		@Override
		public String toString() {
			return "i8";
		}
	},
	float32 {
		@Override
		public String toString() {
			return "f4";
		}
	},
	float64 {
		@Override
		public String toString() {
			return "f8";
		}
	}
}
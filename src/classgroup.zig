const std = @import("std");
const bigInt = std.math.big.int;
const HKZbasis = @import("HKZbasis.zig");

pub var cn: bigInt = undefined;
pub var half_cn: bigInt = undefined;
pub var babai_Ainv_row: [74]bigInt = undefined;

pub var IP: [74]bigInt = undefined;
pub var B: [74]bigInt = undefined;

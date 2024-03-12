const std = @import("std");
const bigInt = std.math.big.int;
const HKZbasis = @import("HKZbasis.zig");

pub const classgroup = struct {
    cn: bigInt,
    half_cn: bigInt,
    twopow: bigInt,
    babai_Ainv_row: [74]bigInt,
    IP: [74]bigInt,
    B: [74]bigInt,
    A: [74 * 74]bigInt,
    allocator: std.mem.Allocator,

    const Self = @This();

    pub fn init(self: Self) !void {
        try self.cn.Managed.init(self.allocator);
        try self.twopow.Managed.init(self.allocator);

        for (self.babai_Ainv_row) |i| {
            try self.babai_Ainv_row[i].Managed.init(self.allocator);
        }
    }
};

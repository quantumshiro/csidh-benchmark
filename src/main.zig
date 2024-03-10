const std = @import("std");
const c = @cImport({
    @cInclude("include/csidh.h");
    @cInclude("include/params.h");
    @cInclude("include/fp.h");
});

pub fn main() !void {
    std.debug.print("Hello, world!\n", .{});
}

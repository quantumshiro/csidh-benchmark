const std = @import("std");
const crypto = std.crypto;
const sha256 = crypto.hash.sha3.Sha3_256;

const Hash = [32]u8;

pub fn leafHash(data: []u8) Hash {
    var h: Hash = undefined;
    sha256.hash(data[0..], h[0..], .{});
    return h;
}

pub fn nodeHash(left: Hash, right: Hash) Hash {
    var buf: [64]u8 = undefined;
    std.mem.copyBackwards(u8, buf[0..32], left[0..]);
    std.mem.copyBackwards(u8, buf[32..], right[0..]);
    return leafHash(buf[0..]);
}

const Forest = struct {
    const self = @This();

    trees: [64]Hash, // [64][32]u8
    leaves: u64,

    pub fn reset(ctx: *self) void {
        ctx.leaves = 0;
    }

    pub fn init() self {
        var ctx: self = undefined;
        ctx.reset();
        return ctx;
    }

    pub fn hight(ctx: *self, high: u6) bool {
        return ctx.leaves & (@as(u64, 1) << high) != 0;
    }

    pub fn add(ctx: *self, leaf: []u8) void {
        var tree: Hash = leafHash(leaf);
        var i: u6 = 0;
        while (ctx.hight(i)) : (i += 1) {
            tree = nodeHash(ctx.trees[i], tree);
        }
        ctx.trees[i] = tree;
        ctx.leaves += 1;
    }

    pub fn root(ctx: *self) Hash {
        var i: u8 = @ctz(ctx.leaves);
        var r: Hash = ctx.trees[i];
        i += 1;
        while (i < 64) : (i += 1) {
            if (ctx.hight(@intCast(@as(u8, i)))) {
                r = nodeHash(ctx.trees[i], r);
            }
        }
        return r;
    }
};

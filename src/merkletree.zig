const std = @import("std");
const crypto = std.crypto;
const sha256 = crypto.hash.sha3.Sha3_256;

const Hash = [32]u8;

pub fn leafHash(data: []u8) Hash {
    const h: Hash = undefined;
    sha256.hash(data, h);
    return h;
}

pub fn nodeHash(left: Hash, right: Hash) Hash {
    const buf: [64]u8 = undefined;
    std.mem.copyBackwards(u8, buf, left);
    std.mem.copyBackwards(u8, buf, right);
    return leafHash(buf);
}

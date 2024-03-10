const std = @import("std");
const c = @cImport({
    @cInclude("csidh.h");
    @cInclude("params.h");
    @cInclude("fp.h");
});

pub fn main() !void {
    var priv_alice: c.private_key = undefined;
    var priv_bob: c.private_key = undefined;
    var pub_alice: c.public_key = undefined;
    var pub_bob: c.public_key = undefined;
    var share_alice: c.public_key = undefined;
    var shared_bob: c.public_key = undefined;

    c.csidh_private(&priv_alice);
    c.csidh_private(&priv_bob);

    c.csidh(&pub_alice, &c.base, &priv_alice);
    std.debug.print("pub_alice: {}\n", .{pub_alice});

    c.csidh(&pub_bob, &c.base, &priv_bob);
    std.debug.print("pub_bob: {}\n", .{pub_bob});

    c.csidh(&share_alice, &pub_bob, &priv_alice);
    std.debug.print("share_alice: {}\n", .{share_alice});

    c.csidh(&shared_bob, &pub_alice, &priv_bob);
    std.debug.print("shared_bob: {}\n", .{shared_bob});

    if (std.mem.eql(u8, std.mem.asBytes(&share_alice), std.mem.asBytes(&shared_bob))) {
        std.debug.print("Shared secret is equal\n", .{});
    } else {
        std.debug.print("Shared secret is not equal\n", .{});
    }
}

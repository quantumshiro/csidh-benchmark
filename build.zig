const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "csidh_benchmark",
        .target = target,
        .optimize = optimize,
    });
    exe.addIncludePath(.{ .path = "src/include" });
    exe.addCSourceFile(.{ .file = .{ .path = "src/main.cpp" } });
    exe.addCSourceFiles(.{
        .files = &.{
            "src/constants.c",
            "src/csidh.c",
            "src/fp.c",
            "src/mont.c",
            "src/rng.c",
            "src/uint.c",
        },
    });
    exe.linkLibC();
    exe.linkLibCpp();
    exe.linkSystemLibrary("c");

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}

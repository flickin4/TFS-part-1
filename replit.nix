{ pkgs }: {
	deps = [
		pkgs../a
  pkgs.unixtools.util-linux
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}
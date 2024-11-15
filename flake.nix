{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };
  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem
      (system:
        let
          pkgs = import nixpkgs {
            inherit system;
          };
          
          buildInputs = with pkgs; [
            gcc
            xorg.libX11 xorg.libXcursor xorg.libXi xorg.libXrandr # x11
            libGL
            pkg-config
          ];
        in
        with pkgs;
        {
          devShells.default = mkShell {
	          inherit buildInputs;
          };
        }
      );
}

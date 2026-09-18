# Resource downloads

[GitHub Release](https://github.com/CianZhang/smart-waste-sorting/releases/tag/resources-v1)

The deployment model is included in the source repository. Download the following assets separately.

| Asset | Size |
| --- | ---: |
| [training-data-and-history.zip](https://github.com/CianZhang/smart-waste-sorting/releases/download/resources-v1/training-data-and-history.zip) | 1483.67 MB |
| [stepper-motor-vendor-resources.zip](https://github.com/CianZhang/smart-waste-sorting/releases/download/resources-v1/stepper-motor-vendor-resources.zip) | 458.77 MB |
| [legacy-projects-and-provincial-originals.zip](https://github.com/CianZhang/smart-waste-sorting/releases/download/resources-v1/legacy-projects-and-provincial-originals.zip) | 202.93 MB |
| [1.mp4](https://github.com/CianZhang/smart-waste-sorting/releases/download/resources-v1/1.mp4) | 158.4 MB |
| [yolov8.zip.part001](https://github.com/CianZhang/smart-waste-sorting/releases/download/resources-v1/yolov8.zip.part001) | 1500.0 MB |
| [yolov8.zip.part002](https://github.com/CianZhang/smart-waste-sorting/releases/download/resources-v1/yolov8.zip.part002) | 1500.0 MB |
| [yolov8.zip.part003](https://github.com/CianZhang/smart-waste-sorting/releases/download/resources-v1/yolov8.zip.part003) | 978.8 MB |

## Contents

- `1.mp4`: place in `software/raspberry-pi/qml/1.mp4`.
- `training-data-and-history.zip`: training images, labels, historical weights, results, and training projects. Original directory structure is preserved.
- `stepper-motor-vendor-resources.zip`: complete motor vendor documentation, tools, examples and videos.
- `legacy-projects-and-provincial-originals.zip`: legacy STM32 project including build outputs, and original provincial competition archives.
- `yolov8.zip.part001` through `part003`: byte-exact parts of the original yolov8.zip. Download all three before merging.

## Merge yolov8.zip

macOS / Linux:

```sh
cat yolov8.zip.part001 yolov8.zip.part002 yolov8.zip.part003 > yolov8.zip
```

Windows CMD:

```bat
copy /b yolov8.zip.part001+yolov8.zip.part002+yolov8.zip.part003 yolov8.zip
```

Merged file SHA-256:

```text
67cd5b0eae3dfe495bd9983304eb3f1da0dc6049562c12e1c48cc26f418390c0  yolov8.zip
```

See [SHA256SUMS.txt](SHA256SUMS.txt) and [manifest.json](manifest.json) for asset checksums and source inventory. On macOS run `shasum -a 256 -c SHA256SUMS.txt`; on Linux run `sha256sum -c SHA256SUMS.txt`.

Local bundles are stored in the visible `release-assets/` folder; Git tracks only documentation and manifests. Original files remain in `.local-archive/original/`. System images and personal initialization notes are excluded. Historical code and model files have not been executed or loaded.

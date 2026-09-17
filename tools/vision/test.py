"""Run image inference and save result_<i>.jpg without touching hardware."""
import argparse
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, required=True, help="Input image or image directory")
    parser.add_argument("--weights", type=Path, default=ROOT / "software/raspberry-pi/yolo/best.pt")
    parser.add_argument("--output", type=Path, default=ROOT / "outputs/test_result")
    args = parser.parse_args()
    for path in (args.source, args.weights):
        if not path.exists():
            parser.error(f"File or directory does not exist: {path}")
    if not args.weights.is_file():
        parser.error("--weights must name an existing model file")
    from ultralytics import YOLO
    model = YOLO(str(args.weights))
    results = model(str(args.source))
    args.output.mkdir(parents=True, exist_ok=True)
    for index, result in enumerate(results):
        result.save(str(args.output / f"result_{index}.jpg"))


if __name__ == "__main__":
    main()

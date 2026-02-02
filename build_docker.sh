#!/bin/bash
NAMESPACE="${1:-codebase_b570_app}"
docker build -t "$NAMESPACE" .
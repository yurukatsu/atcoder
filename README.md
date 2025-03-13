# atcoder

Atcoder で遊ぶための場所

## 環境構築

1. build

    ```bash
    docker compose build
    ```

2. run

    ```bash
    docker compose up -d
    ```

3. Enter your container

4. load contest (See [here](https://github.com/kyuridenamida/atcoder-tools?tab=readme-ov-file#gen-%E3%81%AE%E8%A9%B3%E7%B4%B0))

    ```bash
    atcoder-tools gen --lang cpp --without-login --workspace ./contest   abc300
    ```

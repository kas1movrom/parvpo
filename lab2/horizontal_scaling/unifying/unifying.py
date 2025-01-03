from flask import Flask, request, jsonify
import time

app = Flask(__name__)

pnum = None
received_count = 0
partial_results = []
start_time = 0.0

@app.route('/partial', methods=['POST'])
def handle_partial():
    global pnum, received_count, partial_results, start_time

    # Считываем заголовки
    pid         = int(request.headers.get("pid", "0"))
    pnum_header = int(request.headers.get("pnum", "1"))
    time_spent  = float(request.headers.get("time-spent", "0.0"))

    # Если ещё не знаем, сколько consumer-ов, и это первая часть
    if pnum is None:
        pnum = pnum_header
        partial_results = [None]*pnum
        start_time = time.time()  # время прихода первого куска

    # Считываем кусок матрицы (строка вида "1,2,3,...")
    data_str = request.data.decode("utf-8")
    arr = list(map(int, data_str.split(",")))
    partial_results[pid] = arr
    received_count += 1
    x_time += time_spent

    print(f"[Aggregator] Received piece from consumer {pid}, size={len(arr)}, local_time={time_spent:.2f} ms")

    if received_count == pnum:
        # Все куски получены
        end_time = time.time()
        total_time_ms = (end_time - start_time + x_time)*1000
        total_time_ms

        # Склеиваем
        final_matrix = []
        for part in partial_results:
            final_matrix += part  # просто конкатенация

        print(f"[Unifying] All pieces are received!")
        print(f"[Unifying] Final matrix size = {len(final_matrix)}")
        print(f"[Unifying] Total time from 1st piece to last = {total_time_ms:.2f} ms")

    return jsonify({"status": "ok"}), 200

if __name__ == '__main__':
    print("[Unifying] Starting on 8080...")
    app.run(host='0.0.0.0', port=8080)

FROM python:3.10-slim

WORKDIR /unifying
COPY unifying.py .

RUN pip install flask requests

EXPOSE 8080
CMD ["python", "aggregator.py"]

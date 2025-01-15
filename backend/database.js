const dotenv = require('dotenv');
const mysql = require('mysql2');

dotenv.config();

const connection = mysql.createPool({
  host: process.env.SQL_SERVER_HOST,
  user: process.env.SQL_SERVER_USER,
  database: process.env.SQL_SERVER_DATABASE,
  password: process.env.SQL_SERVER_PASSWORD || '',
  port: process.env.SQL_SERVER_PORT || 3306, // default if not specified
  connectTimeout: 10_000,
  waitForConnections: true,
  connectionLimit: 10,
  queueLimit: 1,
});

module.exports = connection;

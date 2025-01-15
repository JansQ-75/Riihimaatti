const db = require('../database');

const transaction = {
  getAll: (callback) => {
    return db.query('SELECT * FROM transaction;', callback);
  },
  // Todo
};

module.exports = transaction;

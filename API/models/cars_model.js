const db = require('../database');

const cars = {
  getAll: function(callback) {
    return db.query('select * from cars', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from cars where ID=?', [id], callback);
  },
  add: function(cars, callback) {
    return db.query(
      'insert into cars (brand,model) values(?,?)',
      [cars.brand,cars.model],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from cars where ID=?', [id], callback);
  },
  update: function(id, cars, callback) {
    return db.query(
      'update cars set brand=?,model=? where ID=?',
      [cars.brand,cars.model,id],
      callback
    );
  }
};
module.exports = cars;
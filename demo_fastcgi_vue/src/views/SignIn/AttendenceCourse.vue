<template>
    <div>
        <div class="crumbs">
            <el-breadcrumb separator="/">
                <el-breadcrumb-item> <i class="el-icon-lx-cascades"></i> 当前课程 </el-breadcrumb-item>
            </el-breadcrumb>
        </div>
        <div class="container">
            <el-table :data="tableData" border class="table" ref="multipleTable" header-cell-class-name="table-header">
                <el-table-column type="selection" width="40" align="center"></el-table-column>
                <el-table-column prop="courseID" label="课程号" align="center"></el-table-column>
                <el-table-column prop="courseName" label="课程名" align="center"></el-table-column>
                <el-table-column prop="teacherName" label="授课教师" align="center"></el-table-column>
                <el-table-column prop="courseDay" label="星期" align="center"></el-table-column>
                <el-table-column prop="courseTime" label="上课时间" align="center"></el-table-column>
                <el-table-column prop="classRoomID" label="上课地点" align="center"></el-table-column>
                <el-table-column prop="" label="起始节" align="center">
                    <template slot-scope="scope">{{ scope.row.coursePeriodF }}-{{ scope.row.coursePeriodB }}节</template>
                </el-table-column>
                <el-table-column label="操作" width="180" align="center">
                    <template slot-scope="scope">
                        <el-button type="text" icon="el-icon-mouse" class="blue" @click="handleMore(scope.$index, scope.row)"
                            >考勤</el-button
                        >
                    </template>
                </el-table-column>
            </el-table>
            <div class="pagination">
                <el-pagination
                    background
                    layout="total, prev, pager, next"
                    :current-page="query.currentPage"
                    :page-size="query.pageSize"
                    :total="query.pageTotal"
                ></el-pagination>
            </div>
        </div>
    </div>
</template>

<script>
import { fetchData, AvatarData } from '../../api/index';
import JsonExcel from 'vue-json-excel';
const weekArr = ['星期日', '星期一', '星期二', '星期三', '星期四', '星期五', '星期六'];
export default {
    name: 'basetable',
    inject: ['reload'],
    data() {
        return {
            query: {
                address: '',
                name: '',
                currentPage: 1,
                pageSize: 5,
                pageTotal: 0,
                request: ''
            },
            form: {
                options: []
            },
            //给子组件的值
            dataParams: {},
            tableData: [],
            list: [{}],
            weeks: {
                0: '星期日',
                1: '星期一',
                2: '星期二',
                3: '星期三',
                4: '星期四',
                5: '星期五',
                6: '星期六'
            }
        };
    },
    components: {},
    created() {
        this.getData(); //渲染
    },

    methods: {
        // 获取后台数据
        getData() {
            const that = this;
            var aData = new Date();
            this.dataDateNumber(aData);
            //console.log(this.dataDateNumber(aData));
            if (this.$store.getters.getUser.roseID == '1') {
                const params = { params: { tID: this.$store.getters.getUser.userID, cID: null, cD: this.dataDateNumber(aData) } };
                const that = this;
                //axios的get请求
                this.$axios
                    .get('/api/scourse/findScourseBytIDcIDcD', params)
                    .then((res) => {
                        //console.log(res);
                        this.form = res.data;
                        //console.log('请求后台数据结果', this.form);
                        this.dataTraversal(this.form);
                    })
                    .catch((err) => {
                        console.log(err);
                    });
            }
        },
        dataTraversal(form) {
            this.list = [];
            this.newArray = [];
            let id = 0;
            for (const i in form) {
                //console.log('属性:' + i);
                for (const key in form[i].course) {
                    this.$set(this.list, key, form[i].course[key]); //对象新增属性(使用Vue.$set())
                    this.newArray[i] = this.list; //新建数组存放
                }
                for (const key in form[i].student) {
                    //console.log("属性:"+key);
                    this.$set(this.list, key, form[i].student[key]); //对象新增属性(使用Vue.$set())
                    this.newArray[i] = this.list; //新建数组存放
                }
                for (const key in form[i].teacher) {
                    //console.log("属性:"+key);
                    this.$set(this.list, key, form[i].teacher[key]); //对象新增属性(使用Vue.$set())
                    this.newArray[i] = this.list; //新建数组存放
                }

                this.list = []; //循环完必须清空,否则可能会覆盖
            }
            //console.log(this.newArray);
            this.tableData = this.newArray;
            this.query.currentPage = 1;
            this.query.pageTotal = form.length;
            this.query.pageSize = form.length;
        },
        //根据当前的日期显示当前是星期几
        dataDateChange(dateStr) {
            if (dateStr != null || dateStr == '') {
                let date = new Date(dateStr);
                let weekIndex = date.getDay();
                //this.week = this.weeks[weekIndex];
                return this.weeks[weekIndex];
            } else return null;
        },
        //根据当前的日期显示当前是星期几的索引
        dataDateNumber(dateStr) {
            if (dateStr != null || dateStr == '') {
                let date = new Date(dateStr);
                let weekIndex = date.getDay();
                return weekIndex;
            } else return null;
        },
        handleMore(index, row) {
            this.idx = index;
            this.dataParams = row;
            //将数组转成对象
            var obj = {};
            for (var i in row) {
                obj[i] = row[i];
            }
            this.dataParams = obj;
            sessionStorage.setItem('dataParams', JSON.stringify(this.dataParams));
            this.showUsualCourseDialog = false;
            this.$router.push({ path: '/SignIn', query: { data: this.dataParams } }); //路由跳转传参
        }
    }
};
</script>

<style scoped>
.handleUpload {
    position: relative;
    margin-left: 850px;
    margin-top: -32px;
}
.handle-box {
    margin-bottom: 20px;
    display: block;
}
.handle-line {
    margin-top: 8px;
}
.handle-weekday {
    position: relative;
    margin-left: 570px;
    margin-top: -32px;
}

.handle-select {
    width: 120px;
}

.handle-input {
    width: 120px;
    display: inline-block;
}
/* .close {
    margin: 0 0 0 -30px;
} */

.table {
    width: 100%;
    font-size: 14px;
}
.red {
    color: #ff0000;
}
.blue {
    color: #2f00ff;
}
.mr10 {
    margin-right: 10px;
}
.table-td-thumb {
    display: block;
    margin: auto;
    width: 40px;
    height: 40px;
    cursor: pointer;
}

.table-td-thumb.el-icon-circle-close {
    color: white;
}
.handle-add {
    color: rgb(6, 49, 240);
}
</style>
